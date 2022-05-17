// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <functional>

namespace ecs
{

class Entity;

template<typename... Ts>
class Iterator
{
public:
	std::pair<Entity&, std::tuple<Ts&...>> operator*()
	{
		return std::tie();
	}

	bool operator!=(const Iterator& rhs) const
	{
	}

	Iterator& operator++()
	{
	}

private:
};

template<typename... Ts>
class View
{
public:
	using iterator = Iterator<Ts...>;

	void each(std::function<void(Entity&, Ts&...)> func)
	{
	}

	iterator begin()
	{
	}

	iterator end()
	{
	}

	const iterator begin() const
	{
	}

	const iterator end() const
	{
	}

private:
};

}
