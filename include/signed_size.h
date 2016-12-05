#include <cassert>
#include <cstddef>
#include <limits>
#include <type_traits>

// When using int loop indices, use signed_size(container) instead of
// container.size() in order to document the inherent assumption that the size
// of the container can be represented by an int.
// If int is too small, use sane_size<int64_t>(container).

template <typename Signed = int, typename Container>
#if __cplusplus==201402L
constexpr Signed signed_size(const Container &c) {
#else
/*constexpr*/ Signed signed_size(const Container &c) {
#endif
    static_assert(std::is_signed<Signed>(), "signed_size expects signed template parameter");
    const auto size = c.size();
    assert(size <= static_cast<decltype(size)>(std::numeric_limits<Signed>::max()));
    return static_cast<Signed>(size);
}
