// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <chrono>
#include <string>
#include <thread>

class Session;

struct CpuSample
{
	std::string_view                          name;
	std::chrono::duration<double, std::micro> start;
	std::chrono::microseconds                 elapsed;
	std::thread::id                           threadId;
};

class Counter
{
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;

public:
	/**
	 * @brief 构造函数.
	 *
	 * @note 被调用时开始计时.
	 */
	Counter(std::string_view name, Session& s);

	/**
	 * @brief 析构函数.
	 *
	 * @note 被调用时停止计时, 并将样本数据写入所属的 Session.
	 */
	virtual ~Counter();

	/**
	 * @brief 停止计时.
	 *
	 * @node 有时需要在析构函数自动调用前停止计时.
	 */
	void stop();

private:
	bool       stopped;
	time_point begin;
	CpuSample  sample;
	Session&   session;
};
