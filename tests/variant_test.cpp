#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "variant.hpp"

using namespace demo;

TEST(AVariant, CanBeCreated) { const auto variant = Variant{}; }
