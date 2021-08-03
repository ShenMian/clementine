// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vector>

class Session;

/**
 * @brief 性能分析器, 测控式剖析器(instrumental profiler).
 * 支持以不同的格式导出样本数据. 包括可用浏览器 Tracking 分析的 JSON 格式.
 */
class Profiler
{
public:
    static Profiler& get();

    void addSession(Session& s);

private:
    std::vector<Session> sessions;
};
