// Copyright 2021 SMS
// License(Apache-2.0)

#include "Counter.h"
#include "Session.h"

using namespace std::chrono;

Counter::Counter(std::string_view n, Session& s)
		: stopped(false), begin(steady_clock::now()), session(s)
{
	sample.name     = n;
	sample.threadId = std::this_thread::get_id();
}

Counter::~Counter()
{
	if(!stopped)
		stop();
}

void Counter::stop()
{
	stopped        = true;
	auto end       = steady_clock::now();
	sample.start   = begin.time_since_epoch();
	sample.elapsed = time_point_cast<microseconds>(end).time_since_epoch() - time_point_cast<microseconds>(begin).time_since_epoch();
	session.addCpuSample(sample);
}