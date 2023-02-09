// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include <chrono>

namespace core
{

/**
 * @brief 计时器.
 *
 * 构造时开始计时, 调用成员函数来获取经过的时间.
 */
class Timer
{
public:
	Timer() : start_(std::chrono::high_resolution_clock::now()) {}

	/**
	 * @brief 获取经过的秒数.
	 */
	double getSeconds() const { return getMilliseconds() / 1000.0; }

	/**
	 * @brief 获取经过的毫秒数.
	 */
	double getMilliseconds() const { return getMilliseconds() / 1000.0; }

	/**
	 * @brief 获取经过的微秒数.
	 */
	double getMicroseconds() const
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start_)
		    .count();
	}

private:
	std::chrono::high_resolution_clock::time_point start_;
};

} // namespace core
