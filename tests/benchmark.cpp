// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "ecs/component.hpp"
#include "ecs/manager.hpp"
#include "ecs/packed_array.hpp"
#include "ecs/view.hpp"
#include <doctest/doctest.h>
#include <nanobench.h>

#include <cassert>
#include <iostream>

using namespace ankerl;

struct AComponent : public ecs::Component
{
	DECLARE_TYPE

	uint32_t value;
};

struct BComponent : public ecs::Component
{
	DECLARE_TYPE

	uint32_t value;
};

TEST_SUITE_BEGIN("benchmark");

TEST_CASE("PackedArray add component" * doctest::skip(true))
{
	nanobench::Bench bench;
	// TODO: std::views::iota(4) | std::views::transform([](auto i) { return std::pow(2, i); }) | std::views::take(12);
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		bench.complexityN(size).run("create " + std::to_string(size) + " elements in the packed array", [&] {
			ecs::PackedArray<AComponent> array;
			for(size_t i = 0; i < size; i++)
				// nanobench::doNotOptimizeAway(array[i]);
				array.insert(i);
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("PackedArray get component" * doctest::skip(true))
{
	nanobench::Bench bench;
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		ecs::PackedArray<AComponent> array;
		for(size_t i = 0; i < size; i++)
			array[i].value = i;
		bench.complexityN(size).run("get " + std::to_string(size) + " elements in the packed array", [&] {
			for(size_t i = 0; i < size; i++)
				nanobench::doNotOptimizeAway(array[i]);
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("PackedArray remove component" * doctest::skip(true))
{
	nanobench::Bench bench;
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		ecs::PackedArray<AComponent> array;
		for(size_t i = 0; i < size; i++)
			array[i].value = i;
		bench.complexityN(size).run("remove " + std::to_string(size) + " elements in the packed array", [&] {
			auto arr = array;
			for(size_t i = 0; i < size; i++)
				arr.remove(i);
			CHECK(arr.size() == 0);
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("create entities" * doctest::skip(true))
{
	nanobench::Bench bench;
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		bench.complexityN(size).run("create " + std::to_string(size) + " entities with 2 components", [&] {
			ecs::Manager manager;
			for(size_t i = 0; i < size; i++)
				manager.add_components<AComponent, BComponent>(manager.create());
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("destroy entities" * doctest::skip(true))
{
	nanobench::Bench bench;
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		ecs::Manager manager;
		for(size_t i = 0; i < size; i++)
			manager.add_components<AComponent, BComponent>(manager.create());
		bench.complexityN(size).run("destroy " + std::to_string(size) + " entities with 2 components", [&] {
			for(size_t i = 0; i < size; i++)
				manager.destroy(ecs::Entity(i, 1));
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("unpack components" * doctest::skip(true))
{
	nanobench::Bench bench;
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		ecs::Manager manager;
		for(size_t i = 0; i < size; i++)
			manager.add_components<AComponent, BComponent>(manager.create());
		manager.add_group<AComponent, BComponent>();
		bench.complexityN(size).run("unpack two components in " + std::to_string(size) + " entities", [&] {
			auto view = ecs::View<AComponent, BComponent>(manager.get_group<AComponent, BComponent>(), manager);
			for(auto [e, a, b] : view)
			{
				nanobench::doNotOptimizeAway(a);
				nanobench::doNotOptimizeAway(b);
			}
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_CASE("unpack components (const)" * doctest::skip(true))
{
	nanobench::Bench bench;
	for(const auto size :
	    {16, 64, 256, 1 * 1000, 4 * 1000, 16 * 1000, 65 * 1000, 262 * 1000, 1000 * 1000, 2 * 1000 * 1000})
	{
		ecs::Manager manager;
		for(size_t i = 0; i < size; i++)
			manager.add_components<AComponent, BComponent>(manager.create());
		manager.add_group<AComponent, BComponent>();
		bench.complexityN(size).run("unpack two components in " + std::to_string(size) + " entities", [&] {
			const auto view = ecs::View<AComponent, BComponent>(manager.get_group<AComponent, BComponent>(), manager);
			for(auto [e, a, b] : view)
			{
				nanobench::doNotOptimizeAway(a);
				nanobench::doNotOptimizeAway(b);
			}
		});
	}
	// std::cout << bench.complexityBigO() << std::endl;
}

TEST_SUITE_END;
