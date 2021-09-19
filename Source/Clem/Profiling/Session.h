// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Recorder.h"
#include <string>
#include <vector>

namespace clem
{

/**
 * @addtogroup Profiling
 * @{
 */

/**
 * @brief 会话.
 *
 * 记录 CPU 样本.
 */
class Session
{
public:
    void addCpuSample(const CpuSample&);
    void clear();

private:
    std::string            name;
    std::vector<CpuSample> samples;
};

/**
 * end of Profiling group
 * @}
 */

} // namespace clem