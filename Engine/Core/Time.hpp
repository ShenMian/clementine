// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <chrono>

// TODO: 可能被弃用, 使用 chrono 内提供的类型替代

namespace core
{

class Time
{
public:
	/**
	 * @brief 获取以秒为单位的时间.
	 */
	constexpr float asSeconds() const;

	/**
	 * @brief 获取以毫秒为单位的时间.
	 */
	constexpr uint32_t asMilliseconds() const;

	/**
	 * @brief 获取以微秒为单位的时间.
	 */
	constexpr uint64_t asMicroseconds() const;

	/**
	 * @brief 以秒为单位创建时间.
	 */
	constexpr static Time seconds(float sec);

	/**
	 * @brief 以毫秒为单位创建时间.
	 */
	constexpr static Time milliseconds(uint32_t ms);

	/**
	 * @brief 以微秒为单位创建时间.
	 */
	constexpr static Time microseconds(uint64_t us);

	auto operator<=>(const Time&) const = default;

private:
	constexpr Time(uint64_t us);

	uint64_t microseconds_;
};

}

#include "Time.inl"
