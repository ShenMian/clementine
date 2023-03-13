// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/check.hpp"
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace ecs
{

class PackedArrayBase
{
};

/**
 * @brief 动态无缝数组.
 *
 * 无缝是为了使其 cache 友好, 提高遍历数组元素的效率.
 *
 * @tparam T 要存放的数据类型.
 */
template <typename T>
class PackedArray : public PackedArrayBase
{
public:
	using size_type = size_t;
	static_assert(std::numeric_limits<size_type>::max() >=
	              std::numeric_limits<typename std::vector<T>::size_type>::max());

	/**
	 * @brief 创建元素.
	 */
	T& insert(size_type index)
	{
		CLEM_DEBUG_CHECK(!index_map_.contains(index));
		return (*this)[index];
	}

	/**
	 * @brief 获取已有元素或创建并返回元素.
	 *
	 * @param 元素的下标.
	 */
	T& operator[](size_type index)
	{
		if(index_map_.contains(index))
			return data_[index_map_[index]];

		CLEM_DEBUG_CHECK(index_map_.size() == data_.size());
		index_map_.insert({index, size()});
		return data_.emplace_back();
	}

	/**
	 * @brief 获取元素.
	 *
	 * @param 要获取元素的下标.
	 */
	const T& operator[](size_type index) const
	{
		CLEM_DEBUG_CHECK(index_map_.contains(index));
		return data_[index_map_.at(index)];
	}

	/**
	 * @brief 移除元素.
	 *
	 * @param 要移除元素的下标.
	 */
	void remove(size_type index)
	{
		CLEM_DEBUG_CHECK(index_map_.contains(index));
		const auto i = index_map_[index];
		if(i < size() - 1)
			data_[i] = data_[size() - 1];
		index_map_.erase(index);
	}

	/**
	 * @brief 获取存放的元素个数.
	 */
	auto size() const noexcept { return index_map_.size(); }

	/**
	 * @brief 获取最大存放的元素个数.
	 */
	auto max_size() const noexcept { return std::min(index_map_.max_size(), data_.max_size()); }

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
		data_.resize(size);
		index_map_.reserve(size);
	}

	/**
	 * @brief 释放未使用的内存.
	 */
	void shrink_to_fit() { data_.resize(index_map_.size()); }

private:
	std::vector<T>                     data_;
	std::unordered_map<size_t, size_t> index_map_;
};

} // namespace ecs
