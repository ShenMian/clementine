// Copyright 2021 SMS
// License(Apache-2.0)

#include "gtest/gtest.h"
#include "clem/math/point.h"
#include "clem/math/vec2.h"

TEST(Point, distance)
{
	EXPECT_EQ(Point(0, 0).distance(Point(3, 4)), 5);
}

TEST(Vec2, length)
{
	EXPECT_EQ(Vec2(3, 4).length(), 5);
}

TEST(Vec2, normorlize)
{
	EXPECT_EQ(Vec2(3, 4).normalize().length(), 1);
	EXPECT_EQ(Vec2(3, 4).normalize(), Vec2(6, 8).normalize());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
