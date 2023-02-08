// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/check.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace ecs
{

/**
 * @brief 动态无缝数组.
 *
 * @tparam T 要存放的数据类型.
 *
 * 无缝是为了使其 cache 友好, 提高遍历数组元素的效率.
 */
template <typename T>
class Array
{
public:
	using size_type = size_t;
	static_assert(std::numeric_limits<size_type>::max() >= std::vector<T>::size_type);

	/**
	 * @brief 获取元素.
	 *
	 * @param 要获取元素的下标.
	 */
	T& operator[](size_type index)
	{
		if(index_.contains(index))
			return data_[index_[index]];

		index_.insert({index, index_.size()});
		return data_.emplace_back();
	}

	/**
	 * @brief 获取元素.
	 *
	 * @param 要获取元素的下标.
	 */
	const T& operator[](size_type index) const
	{
		check(index_.contains(index));
		return data_[index_[index]];
	}

	/**
	 * @brief 移除元素.
	 *
	 * @param 要移除元素的下标.
	 */
	void remove(size_type index)
	{
		check(index_.contains(index));
		const auto i = index_[index];
		if(i < size() - 1)
			data_[i] = data_[size() - 1];
		index_.erase(index);
	}

	/**
	 * @brief 获取存放的元素个数.
	 */
	auto size() const noexcept { return index_.size(); }

	/**
	 * @brief 获取最大存放的元素个数.
	 */
	auto max_size() const noexcept { return std::min(index_.max_size(), data_.max_size()); }

	/**
	 * @brief 获取预留存放的元素个数.
	 */
	auto capacity() const noexcept { return data_.size(); }

	/**
	 * @brief 设置预留存放的元素个数.
	 *
	 * @param size 预留存放的元素个数.
	 */
	void reserve(size_type size)
	{
		return data_.resize(size);
		index_.reserve(size);
	}

	/**
	 * @brief 释放未使用的内存.
	 */
	void shrink_to_fit() { data_.resize(index_.size()); }

private:
	std::vector<T>                     data_;
	std::unordered_map<size_t, size_t> index_;
};

} // namespace ecs
