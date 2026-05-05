#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "variant.hpp"

using namespace demo;

using testing::Eq;

TEST(AVariant, CanContainInt32Value) {
    const auto variant = make_variant(42);
    const auto value = extract_value<int32_t>(variant);

    ASSERT_TRUE(value.has_value());
    EXPECT_THAT(value.value(), Eq(42));
}

TEST(AVariant, CanContainUInt32ValueValue) {
    const auto variant = make_variant(40u);
    const auto value = extract_value<uint32_t>(variant);

    ASSERT_TRUE(value.has_value());
    EXPECT_THAT(value.value(), Eq(40u));
}

TEST(ExtractValue, ReturnsErrorIfVariantDoesNotContainType) {
    const auto int_32t_variant = make_variant(42);
    const auto value = extract_value<uint32_t>(int_32t_variant);

    ASSERT_FALSE(value.has_value());
    EXPECT_THAT(value.error(), Eq("Variant does not contain uint32_t"));
}