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
	constexpr static Time seconds(float sec)
	{
		check(sec < 0, "cannot be negative");
		check(sec <= std::numeric_limits<uint64_t>::max() / 1000000, "overflow");
		return Time(static_cast<uint64_t>(sec) * 1000000);
	}

	/**
	 * @brief 以毫秒为单位创建时间.
	 */
	constexpr static Time milliseconds(uint32_t ms) { return Time(static_cast<uint64_t>(ms) * 1000); }

	/**
	 * @brief 以微秒为单位创建时间.
	 */
	constexpr static Time microseconds(uint64_t us) { return Time(us); }

	/**
	 * @brief 获取以秒为单位的时间.
	 */
	constexpr auto get_seconds() const { return us_ / 1000000.f; }

	/**
	 * @brief 获取以毫秒为单位的时间.
	 */
	constexpr auto get_milliseconds() const { return us_ / 1000; }

	/**
	 * @brief 获取以微秒为单位的时间.
	 */
	constexpr auto get_microseconds() const { return us_; }

	constexpr auto operator<=>(const Time& rhs) const noexcept = default;
	constexpr Time operator+=(const Time& rhs) noexcept { return us_ += rhs.us_; }

	constexpr Time operator-=(const Time& rhs) noexcept
	{
		check(us_ >= rhs.us_);
		return us_ -= rhs.us_;
	}

	constexpr Time operator+(const Time& rhs) const noexcept { return Time(us_) += rhs; }
	constexpr Time operator-(const Time& rhs) const noexcept { return Time(us_) -= rhs; }

private:
	constexpr Time(uint64_t us) : us_(us) {}

	uint64_t us_;
};

} // namespace core
