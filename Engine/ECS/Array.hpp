// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <unordered_map>
#include <vector>

namespace ecs
{

class Entity;

/**
 * @brief 无缝数组.
 */
template<typename T>
class Array
{
public:
	void add(const Entity& entity, const T& component)
	{
		if(!index_.contains(entity))
			index_.insert({entity, index_.size()});
		const auto index = index[entity];
		if(data_.size() <= index)
			data_.resize(index);
		data_[index] = component;
	}

	void remove(const Entity& entity) noexcept
	{
		const auto index = index[entity];
		index_.erase(entity);
		if(index == data_.size() - 1)
		{
			data_.pop_back();
			return;
		}
		std::swap(data_[index], data_.back());
	}

	auto size() const noexcept
	{
		return index_.size();
	}

private:
	std::vector<T> data_;
	std::unordered_map<Entity, size_t> index_;
};

}
