// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Counter.h"
#include <string>
#include <vector>

class Session
{
public:
	void addCpuSample(const CpuSample&);
	void clear();

private:
	std::string            name;
	std::vector<CpuSample> samples;
};
