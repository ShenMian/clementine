// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem/Clem.h"
#include "gtest/gtest.h"

TEST(Size2, area)
{
    EXPECT_EQ(Vector2(3, 4).area(), 3 * 4);
}

TEST(Point2, distance)
{
    EXPECT_EQ(Point2(3, 4).distance(Point2(3 + 3, 4 + 4)), 5);
}

TEST(Point2, distanceSquared)
{
    EXPECT_EQ(Point2(0, 0).distanceSquared(Point2(3, 4)), 5 * 5);
}

TEST(Vector2, size)
{
    EXPECT_EQ(Vector2(3, 4).size(), 5);
}

TEST(Vector2, sizeSquared)
{
    EXPECT_EQ(Vector2(3, 4).sizeSquared(), 5 * 5);
}

TEST(Vector2, normorlize)
{
    EXPECT_EQ(Vector2(3, 4).normalize().size(), 1);
    EXPECT_EQ(Vector2(3, 4).normalize(), Vector2(6, 8).normalize());
}