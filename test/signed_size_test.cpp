#include <gtest/gtest.h>

#include <iostream>
#include "signed_size.h"

TEST(SignedSize, ReturnsThreeForContainerOfSizeThree) {
    auto container = {1, 2, 3};
	ASSERT_EQ(3, signed_size(container));
}
