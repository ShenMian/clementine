// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"
#include "gtest/gtest.h"

using namespace clem;

TEST(Archtype, compare)
{
	auto& a = makeArchtype<Transform, Rigidbody>();
	auto& b = makeArchtype<Rigidbody, Transform>();
	auto& c = makeArchtype<Transform>();
	auto& d = makeArchtype<Rigidbody>();
	EXPECT_EQ(a, b);
	EXPECT_NE(a, c);
	EXPECT_NE(c, d);
}

TEST(Archtype, all)
{
	auto& a = makeArchtype<Transform, Rigidbody>();
	auto  b = a.all<Transform>();
	auto  c = a.all<Rigidbody>();
	auto  d = a.all<Transform, Rigidbody>();
	auto  e = a.all<Tag>();
	EXPECT_TRUE(b);
	EXPECT_TRUE(c);
	EXPECT_TRUE(d);
	EXPECT_FALSE(e);
}