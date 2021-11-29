// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <cassert>
#include <cstdint>
#include <limits>

namespace clem
{

class Time
{
public:
	/**
	 * @brief 获取以秒为单位的时间.
	 */
	auto getSeconds() const;

	/**
	 * @brief 获取以毫秒为单位的时间.
	 */
	auto getMilliseconds() const;

	/**
	 * @brief 获取以微秒为单位的时间.
	 */
	auto getMicroseconds() const;

	/**
	 * @brief 以秒为单位创建时间.
	 */
	static Time seconds(float sec);

	/**
	 * @brief 以毫秒为单位创建时间.
	 */
	static Time milliseconds(uint32_t ms);

	/**
	 * @brief 以微秒为单位创建时间.
	 */
	static Time microseconds(uint64_t us);

private:
	explicit Time(uint64_t us);

	uint64_t us;
};

[[nodiscard]] auto Time::getSeconds() const
{
	return us / 1000000.f;
}

[[nodiscard]] auto Time::getMilliseconds() const
{
	return us / 1000;
}

[[nodiscard]] auto Time::getMicroseconds() const
{
	return us;
}

[[nodiscard]] inline Time Time::seconds(float sec)
{
	assert(sec < 0 && "cannot be negative");
	assert(sec <= std::numeric_limits<uint64_t>::max() / 1000000 && "overflow");
	return Time(static_cast<uint64_t>(sec) * 1000000);
}

[[nodiscard]] inline Time Time::milliseconds(uint32_t ms)
{
	return Time(static_cast<uint64_t>(ms) * 1000);
}

[[nodiscard]] inline Time Time::microseconds(uint64_t us)
{
	return Time(us);
}

Time::Time(uint64_t us)
	: us(us)
{
}

} // namespace clem
