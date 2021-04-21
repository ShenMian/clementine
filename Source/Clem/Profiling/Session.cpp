// Copyright 2021 SMS
// License(Apache-2.0)

#include "Session.h"
#include "Recorder.h"

// TODO: 利用移动语义提高性能
void Session::addCpuSample(const CpuSample& s)
{
	samples.emplace_back(s);
}

void Session::clear()
{
	samples.clear();
}