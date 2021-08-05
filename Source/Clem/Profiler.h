﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <chrono>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

struct ProfileRecord
{
    std::string                               name;
    std::chrono::duration<double, std::micro> start;
    std::chrono::microseconds                 elapsed;
    std::thread::id                           threadId;
};

/**
 * 性能分析器.
 */
class Instrumentor
{
public:
    static Instrumentor& get();

    void begin(const char* filename);
    void end();

    void writeRecord(const ProfileRecord& record);

private:
    ~Instrumentor();
    void writeHead();
    void writeFooter();

    std::mutex    mutex;
    std::ofstream file;
    bool          session = false;
};

/**
 * 计时器.
 */
class InstrumentationCounter
{
public:
    explicit InstrumentationCounter(const char* name);
    ~InstrumentationCounter();

    void stop();

private:
    const char*                                        name;
    bool                                               stopped;
    std::chrono::time_point<std::chrono::steady_clock> begin;
};

#if USE_PROFILER
#    define PROFILE_SESSION_BEGIN(filepath) Instrumentor::get().begin(filepath)
#    define PROFILE_SESSION_END()           Instrumentor::get().end()
#    define PROFILE_SCOPE_BEGIN(name)       InstrumentationCounter counter_##name(#    name)
#    define PROFILE_SCOPE_END(name)         counter_##name.stop()
#    define PROFILE_SCOPE                   PROFILE_SCOPE_BEGIN
#    define PROFILE_FUNC()                  InstrumentationCounter counter_##name(__FUNCTION__) /* __FUNCSIG__ */
#else
#    define PROFILE_SESSION_BEGIN(filepath)
#    define PROFILE_SESSION_END()
#    define PROFILE_SCOPE_BEGIN(name)
#    define PROFILE_SCOPE_END(name)
#    define PROFILE_SCOPE
#    define PROFILE_FUNC()
#endif