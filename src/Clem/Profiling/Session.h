// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Recorder.h"
#include <string>
#include <vector>

/**
 * @brief 对样本进行分组.
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
