// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>

namespace clem
{

/**
 * @brief 时间.
 *
 * 表示不同时间单位的时间间隔.
 *
 * @waring 不能表示负数.
 */
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
    Time(uint64_t us);

    uint64_t microseconds_;
};

} // namespace clem
