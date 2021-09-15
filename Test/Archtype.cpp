// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem/Clem.h"
#include "gtest/gtest.h"

using namespace clem;

TEST(Archtype, compare)
{
    const auto& a = makeArchtype<Transform, Rigidbody>();
    const auto& b = makeArchtype<Rigidbody, Transform>();
    const auto& c = makeArchtype<Transform>();
    const auto& d = makeArchtype<Rigidbody>();
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(c, d);
}

TEST(Archtype, all)
{
    const auto& a = makeArchtype<Transform, Rigidbody>();
    auto        b = a.all<Transform>();
    auto        c = a.all<Rigidbody>();
    auto        d = a.all<Transform, Rigidbody>();
    auto        e = a.all<Tag>();
    EXPECT_TRUE(b);
    EXPECT_TRUE(c);
    EXPECT_TRUE(d);
    EXPECT_FALSE(e);
}