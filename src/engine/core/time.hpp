// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "check.hpp"
#include <cstdint>
#include <limits>

namespace core
{

class Time
{
public:
	/**
	 * @brief 以秒为单位创建时间.
	 */
	static Time seconds(float sec)
	{
		check(sec < 0, "cannot be negative");
		check(sec <= std::numeric_limits<uint64_t>::max() / 1000000, "overflow");
		return Time(static_cast<uint64_t>(sec) * 1000000);
	}

	/**
	 * @brief 以毫秒为单位创建时间.
	 */
	static Time milliseconds(uint32_t ms) { return Time(static_cast<uint64_t>(ms) * 1000); }

	/**
	 * @brief 以微秒为单位创建时间.
	 */
	static Time microseconds(uint64_t us) { return Time(us); }
	/**
	 * @brief 获取以秒为单位的时间.
	 */

	auto get_seconds() const { return us_ / 1000000.f; }

	/**
	 * @brief 获取以毫秒为单位的时间.
	 */
	auto get_milliseconds() const { return us_ / 1000; }

	/**
	 * @brief 获取以微秒为单位的时间.
	 */
	auto get_microseconds() const { return us_; }

private:
	Time(uint64_t us) : us_(us) {}

	uint64_t us_;
};

} // namespace core
