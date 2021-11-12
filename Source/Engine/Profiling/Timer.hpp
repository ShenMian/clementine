// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <chrono>

/**
 * @brief 计时器.
 * 
 * 构造时开始计时, 调用成员函数来获取经过的时间.
 */
class Timer
{
public:
	Timer()
		: start(std::chrono::high_resolution_clock::now())
	{
	}

	auto getSeconds() const
	{
		return getMilliseconds() / 1000.0;
	}

	auto getMilliseconds() const
	{
        return getMilliseconds() / 1000.0;
	}

    auto getMicroseconds() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }

private:
	std::chrono::steady_clock::time_point start;
};