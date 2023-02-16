// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "ecs/packed_array.hpp"
#include <doctest/doctest.h>
#include <nanobench.h>

using namespace ankerl;

TEST_SUITE_BEGIN("benchmark");

TEST_CASE("PackedArray" * doctest::skip(true))
{
	ecs::PackedArray<int> array;
	for(size_t i = 0; i < 1000; i++)
		array[i] = i;

	nanobench::Bench().minEpochIterations(100).run("packed array", [&] {
		for(size_t i = 0; i < 1000; i++)
			nanobench::doNotOptimizeAway(array[i]);
	});
}

TEST_SUITE_END;
