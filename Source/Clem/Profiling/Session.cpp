// Copyright 2021 SMS
// License(Apache-2.0)

#include "Session.h"
#include "Recorder.h"

// TODO: �����ƶ������������
void Session::addCpuSample(const CpuSample& s)
{
	samples.emplace_back(s);
}

void Session::clear()
{
	samples.clear();
}