// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <chrono>
#include <string>
#include <thread>

class Session;

/**
 * CPU 样本.
 */
struct CpuSample
{
	std::string_view                          name;
	std::chrono::duration<double, std::micro> start;
	std::chrono::microseconds                 elapsed;
	std::thread::id                           threadId;
};

/**
 * @brief 样本收集器.
 */
class Recorder
{
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;

public:
	/**
	 * @brief 构造函数.
	 *
	 * @note 被调用时开始计时.
	 */
	Recorder(std::string_view name, Session& s);

	/**
	 * @brief 析构函数.
	 *
	 * @note 被调用时停止计时, 并将样本数据写入所属的 Session.
	 */
	virtual ~Recorder();

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
