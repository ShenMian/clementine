// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <chrono>

namespace clem
{

/**
 * @brief 计时器.
 * 
 * 构造时开始计时, 调用成员函数来获取经过的时间.
 */
class Timer
{
public:
	Timer();

	/**
	 * @brief 获取经过的秒数.
	 */
	auto getSeconds() const;

	/**
	 * @brief 获取经过的毫秒数.
	 */
	auto getMilliseconds() const;

	/**
	 * @brief 获取经过的微秒数.
	 */
    auto getMicroseconds() const;

private:
	std::chrono::steady_clock::time_point start;
};

Timer::Timer()
    : start(std::chrono::high_resolution_clock::now())
{
}

[[nodiscard]] auto Timer::getSeconds() const
{
    return getMilliseconds() / 1000.0;
}

[[nodiscard]] auto Timer::getMilliseconds() const
{
    return getMilliseconds() / 1000.0;
}

[[nodiscard]] auto Timer::getMicroseconds() const
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

} // namespace clem