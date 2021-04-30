// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"
#include "gtest/gtest.h"

using namespace clem;

TEST(Archtype, compare)
{
	EXPECT_EQ(Archtype({typeid(Transform), typeid(Rigidbody)}), Archtype({typeid(Rigidbody), typeid(Transform)}));
	EXPECT_NE(Archtype({typeid(Transform)}), Archtype({typeid(Rigidbody)}));
}
