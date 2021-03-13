// Copyright 2021 SMS
// License(Apache-2.0)

#include <gtest/gtest.h>
#include <clem/math/point.h>

TEST(Point, distance)
{
    EXPECT_EQ(Point(0, 0).distance(Point(3, 4)), 5);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
