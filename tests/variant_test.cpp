#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "variant.hpp"

using namespace demo;

using testing::Eq;

TEST(AVariant, CanBeCreated) { const auto variant = Variant{}; }

TEST(AVariant, CanContainInt32Value) {
    const auto variant = Variant{123};

    const auto extracted = variant.extract();
    EXPECT_TRUE(extracted.has_value());
    EXPECT_THAT(extracted.value(), Eq(123));
}