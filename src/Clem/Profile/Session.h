// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <string>
#include <vector>

struct CpuSample;

class Session
{
public:
	void addCpuSample(const CpuSample&);
	void clear();

private:
	std::string                  name;
	std::vector<const CpuSample> samples;
};
