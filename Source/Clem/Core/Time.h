// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>

namespace clem
{

class Time
{
public:
	/**
	 * @brief 获取以秒为单位的时间.
	 */
	float seconds() const;

	/**
	 * @brief 获取以毫秒为单位的时间.
	 */
	uint32_t milliseconds() const;

	/**
	 * @brief 获取以微秒为单位的时间.
	 */
	uint64_t microseconds() const;

private:
	Time(uint64_t us);

	uint64_t microseconds_;

	friend Time seconds(float sec);
	friend Time milliseconds(uint32_t ms);
	friend Time microseconds(uint64_t us);
};

} // namespace clem
