#include <cassert>
#include <cstddef>
#include <limits>
#include <type_traits>

// When using int loop indices, use signed_size(container) instead of
// container.size() in order to document the inherent assumption that the size
// of the container can be represented by an int.
// If int is too small, use sane_size<int64_t>(container).

template <typename SignedIntegral = int, typename Container>
constexpr SignedIntegral signed_size(const Container &c) {
    static_assert(std::is_signed<SignedIntegral>(), "signed_size expects signed template parameter");
    const auto size = c.size();
    assert(size <= static_cast<decltype(size)>(std::numeric_limits<SignedIntegral>::max()));
    return static_cast<SignedIntegral>(size);
}
