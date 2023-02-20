// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "entity.hpp"
#include "manager.hpp"
#include <tuple>
#include <vector>

namespace ecs
{

template <typename... Ts>
class View
{
public:
	class Iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type        = std::tuple<const Entity&, Ts&...>;

		Iterator(std::vector<Entity>::iterator it, Manager& mgr) : iterator_(it), manager_(mgr) {}

		std::tuple<const Entity&, Ts&...> operator*()
		{
			return std::tuple_cat(std::make_tuple(*iterator_), manager_.get_components<Ts...>(*iterator_));
		}

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

	class ConstIterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type        = std::tuple<const Entity&, const Ts&...>;

		ConstIterator(std::vector<Entity>::iterator it, Manager& mgr) : iterator_(it), manager_(mgr){};

		value_type operator*()
		{
			return std::tuple_cat(std::make_tuple(*iterator_), manager_.get_components<Ts...>(*iterator_));
		}

		ConstIterator& operator++() noexcept
		{
			iterator_++;
			return *this;
		}

		ConstIterator operator++(int) noexcept
		{
			Iterator it = *this;
			++(*this);
			return it;
		}

		bool operator==(const ConstIterator& rhs) const noexcept { return iterator_ == rhs.iterator_; };
		bool operator!=(const ConstIterator& rhs) const noexcept { return iterator_ != rhs.iterator_; };

	private:
		mutable std::vector<Entity>::iterator iterator_;
		Manager&                              manager_;
	};

	View(std::vector<Entity>& entities, Manager& manager) : entities_(entities), manager_(manager) {}

	Iterator begin() noexcept { return {entities_.begin(), manager_}; };
	Iterator end() noexcept { return {entities_.end(), manager_}; };

	ConstIterator begin() const noexcept { return {entities_.begin(), manager_}; };
	ConstIterator end() const noexcept { return {entities_.end(), manager_}; };

private:
	std::vector<Entity>& entities_;
	Manager&             manager_;
};

} // namespace ecs
