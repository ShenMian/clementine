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
	 * @brief ���캯��.
	 *
	 * @note ������ʱ��ʼ��ʱ.
	 */
	Counter(std::string_view name, Session& s);

	/**
	 * @brief ��������.
	 *
	 * @note ������ʱֹͣ��ʱ, ������������д�������� Session.
	 */
	virtual ~Counter();

	/**
	 * @brief ֹͣ��ʱ.
	 *
	 * @node ��ʱ��Ҫ�����������Զ�����ǰֹͣ��ʱ.
	 */
	void stop();

private:
	bool       stopped;
	time_point begin;
	CpuSample  sample;
	Session&   session;
};
