// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include "time.hpp"
#include <chrono>

namespace core
{

/**
 * @brief 计时器.
 */
class Timer
{
public:
	using clock = std::chrono::high_resolution_clock;

	/**
	 * @brief 构造函数.
	 *
	 * 开始计时.
	 */
	Timer() : start_(clock::now()) {}

	/**
	 * @brief 重新开始计时.
	 */
	void restart() noexcept { start_ = clock::now(); }

	/**
	 * @brief 获取已经过的时间.
	 */
	Time get_time()
	{
		return Time::microseconds(std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - start_).count());
	}

private:
	clock::time_point start_;
};

} // namespace core
