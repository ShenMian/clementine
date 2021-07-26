// Copyright 2021 SMS
// License(Apache-2.0)

#include "Session.h"
#include "Recorder.h"
#include <utility>

void Session::addCpuSample(const CpuSample& s)
{
	samples.emplace_back(std::move(s));
}

void Session::clear()
{
	samples.clear();
}