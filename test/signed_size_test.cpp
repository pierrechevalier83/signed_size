#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include "signed_size.h"

namespace {

// A fake container that allows testing with large containers without running out of ram
template <typename Size>
struct Container {
    Container(Size s = 0) : size_(s) {}
    Size size() const {
	    return size_;
	}
	Size size_;
};

}

TEST(SignedSize, ReturnsZeroForEmptyVectorOfInts) {
    const std::vector<int> container;
	ASSERT_EQ(0, signed_size(container));
}

TEST(SignedSize, ReturnsZeroForEmptyVectorOfDoubles) {
    const std::vector<double> container;
	ASSERT_EQ(0, signed_size(container));
}

TEST(SignedSize, ReturnsZeroForEmptyVectorWithTemplateSignedType) {
    const std::vector<double> container;
	ASSERT_EQ(0, signed_size<int64_t>(container));
}

TEST(SignedSize, ReturnsThreeForArrayOfSizeThree) {
    const auto container = {1, 2, 3};
	ASSERT_EQ(3, signed_size(container));
}

TEST(SignedSize, ReturnsThreeForVectorOfSizeThree) {
    const std::vector<double> container = {1.0, 2.0, 3.14};
	ASSERT_EQ(3, signed_size(container));
}

TEST(SignedSize, ReturnsThreeForVectorOfSizeThreeWithTemplateSignedType) {
    const std::vector<double> container = {1.0, 2.0, 3.14};
	ASSERT_EQ(3, signed_size<int64_t>(container));
}

TEST(SignedSize, AlsoWorksWithFourtyTwoElements) {
    std::vector<int> container;
	container.resize(42);
	ASSERT_EQ(42, signed_size<int64_t>(container));
}

TEST(SignedSize, ReturnsThreeForCustomContainerOfSizeThree) {
	const Container<size_t> container(3);
	ASSERT_EQ(3, signed_size(container));
}

TEST(SignedSize, WorksOnContainerThatReturnsSignedSizeAlready) {
	const Container<int> container(3);
	ASSERT_EQ(3, signed_size(container));
}


TEST(SignedSize, SucceedsForMaxInt) {
	auto large = static_cast<size_t>(std::numeric_limits<int>::max());
    Container<size_t> container(large);
	ASSERT_EQ(large, signed_size(container));
}

TEST(SignedSize, SucceedsForMaxUnsignedIntWithInt64_t) {
	auto large = std::numeric_limits<unsigned int>::max();
    Container<size_t> container(large);
	ASSERT_EQ(static_cast<int64_t>(large), signed_size<int64_t>(container));
}

TEST(SignedSize, FailsInDebugModeIfContainerIsTooLarge) {
	size_t too_large = std::numeric_limits<int>::max() + 1;
	Container<size_t> container(too_large);
	#ifdef DEBUG
	container.resize(too_large);
	ASSERT_DEATH(signed_size(container));
	#else
	// undefined behaviour... not much to test here.
    #endif
}

#ifdef this_should_not_compile
// TODO: can I use cmake to test this?
TEST(SignedSize, RefusesToReturnUnsignedInt) {
    const std::vector<double> container;
	ASSERT_EQ(0, signed_size<unsigned int>(container));
}
#endif

