// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "entity.hpp"
#include "manager.hpp"
#include <tuple>
#include <vector>

#include <cassert>

namespace ecs
{

template <typename... Ts>
class View
{
public:
	class Iterator
	{
	public:
		Iterator(std::vector<Entity>::iterator it, Manager& manager) : iterator_(it), manager_(manager) {}

		std::tuple<Ts&...> operator*() { return manager_.get_components<Ts...>(*iterator_); }

		Iterator& operator++() noexcept
		{
			iterator_++;
			return *this;
		}

		Iterator operator++(int) noexcept
		{
			Iterator it = *this;
			++(*this);
			return it;
		}

		bool operator==(const Iterator& rhs) const noexcept { return iterator_ == rhs.iterator_; };
		bool operator!=(const Iterator& rhs) const noexcept { return iterator_ != rhs.iterator_; };

	private:
		std::vector<Entity>::iterator iterator_;
		Manager&                      manager_;
	};

	View(std::vector<Entity>& entities, Manager& manager) : entities_(entities), manager_(manager) {}

	Iterator begin() noexcept { return {entities_.begin(), manager_}; };
	Iterator end() noexcept { return {entities_.end(), manager_}; };

private:
	std::vector<Entity>& entities_;
	Manager&             manager_;
};

} // namespace ecs
