// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem/Clem.h"
#include "gtest/gtest.h"

using namespace clem;

// Rect2

TEST(Rect2, right)
{
	EXPECT_EQ(Rect2(Point2(0, 0), Size2(3, 4)).right(), 3);
}

TEST(Rect2, bottom)
{
	EXPECT_EQ(Rect2(Point2(0, 0), Size2(3, 4)).bottom(), -4);
}