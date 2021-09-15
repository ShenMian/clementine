// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <chrono>
#include <string>
#include <thread>

namespace clem
{

class Session;

/**
 * @addtogroup Profiling
 * @{
 */

/**
 * @brief CPU 样本.
 * 包含了一次 CPU 性能分析的数据.
 */
struct CpuSample
{
    std::string_view                          name;     // 样本名称, 比如被测试函数的名称.
    std::chrono::duration<double, std::micro> start;    // 开始时间.
    std::chrono::microseconds                 elapsed;  // 经过的时间.
    std::thread::id                           threadId; // 线程 ID.
};

/**
 * @brief 样本收集器.
 * 进行性能分析并将结果传给指定的 Session.
 */
class Recorder
{
    using time_point = std::chrono::time_point<std::chrono::steady_clock>;

public:
    /**
	 * @brief 构造函数.
	 *
	 * 被调用时开始计时.
	 */
    Recorder(std::string_view name, Session& s);

    /**
	 * @brief 析构函数.
	 *
	 * 若计时未停止调用 stop().
	 */
    virtual ~Recorder();

    /**
	 * @brief 停止计时.
	 *
	 * 停止计时, 并将样本数据写入所属的 Session.
	 */
    void stop();

private:
    bool       stopped;
    time_point begin;
    CpuSample  sample;
    Session&   session;
};

/**
 * end of Profiling group
 * @}
 */

} // namespace clem