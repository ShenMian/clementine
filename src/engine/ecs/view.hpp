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
class ViewIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type        = std::tuple<const Entity&, Ts&...>;

	ViewIterator(std::vector<Entity>::iterator it, Manager& mgr) : iterator_(it), manager_(mgr) {}

	std::tuple<const Entity&, Ts&...> operator*()
	{
		return std::tuple_cat(std::make_tuple(*iterator_), manager_.get_components<Ts...>(*iterator_));
	}

	ViewIterator& operator++() noexcept
	{
		++iterator_;
		return *this;
	}

	ViewIterator operator++(int) noexcept
	{
		ViewIterator it = *this;
		++(*this);
		return it;
	}

	bool operator==(const ViewIterator& rhs) const noexcept { return iterator_ == rhs.iterator_; };
	bool operator!=(const ViewIterator& rhs) const noexcept { return iterator_ != rhs.iterator_; };

private:
	std::vector<Entity>::iterator iterator_;
	Manager&                      manager_;
};

template <typename... Ts>
class ViewConstIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type        = std::tuple<const Entity&, const Ts&...>;

	ViewConstIterator(std::vector<Entity>::iterator it, Manager& mgr) : iterator_(it), manager_(mgr){};

	value_type operator*()
	{
		return std::tuple_cat(std::make_tuple(*iterator_), manager_.get_components<Ts...>(*iterator_));
	}

	ViewConstIterator& operator++() noexcept
	{
		iterator_++;
		return *this;
	}

	ViewConstIterator operator++(int) noexcept
	{
		ViewIterator it = *this;
		++(*this);
		return it;
	}

	bool operator==(const ViewConstIterator& rhs) const noexcept { return iterator_ == rhs.iterator_; };
	bool operator!=(const ViewConstIterator& rhs) const noexcept { return iterator_ != rhs.iterator_; };

private:
	std::vector<Entity>::iterator iterator_;
	Manager&                      manager_;
};

template <typename... Ts>
class View
{
public:
	using iterator       = ViewIterator<Ts...>;
	using const_iterator = ViewConstIterator<Ts...>;

	View(std::vector<Entity>& entities, Manager& manager) : entities_(entities), manager_(manager) {}

	iterator begin() noexcept { return {entities_.begin(), manager_}; };
	iterator end() noexcept { return {entities_.end(), manager_}; };

	const_iterator begin() const noexcept { return {entities_.begin(), manager_}; };
	const_iterator end() const noexcept { return {entities_.end(), manager_}; };

private:
	std::vector<Entity>& entities_;
	Manager&             manager_;
};

} // namespace ecs
