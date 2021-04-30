// Copyright 2021 SMS
// License(Apache-2.0)

#include "gtest/gtest.h"
#include "Clem.h"

using namespace clem;

// ECS
////////////////////////////////

TEST(Archtype, compare)
{
	EXPECT_EQ(Archtype({typeid(Transform), typeid(Rigidbody)}), Archtype({typeid(Rigidbody), typeid(Transform)}));
	EXPECT_NE(Archtype({typeid(Transform)}), Archtype({typeid(Rigidbody)}));
}

////////////////////////////////

// Math
////////////////////////////////

TEST(Point2, distance)
{
	EXPECT_EQ(Point2(0, 0).distance(Point2(3, 4)), 5);
}

TEST(Vec2, length)
{
	EXPECT_EQ(Vec2(3, 4).size(), 5);
}

TEST(Vec2, normorlize)
{
	EXPECT_EQ(Vec2(3, 4).normalize().size(), 1);
	EXPECT_EQ(Vec2(3, 4).normalize(), Vec2(6, 8).normalize());
}

////////////////////////////////

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
