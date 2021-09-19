// Copyright 2021 SMS
// License(Apache-2.0)

#include "Recorder.h"
#include "Core/Assert.hpp"
#include "Session.h"

using namespace std::chrono;

namespace clem
{

Recorder::Recorder(std::string_view n, Session& s)
    : stopped(false), session(s), begin(steady_clock::now())
{
    sample.name     = n;
    sample.threadId = std::this_thread::get_id();
}

Recorder::~Recorder()
{
    if(!stopped)
        stop();
}

void Recorder::stop()
{
    Assert::isFalse(stopped, "recorder has stopped");

    stopped        = true;
    const auto end = steady_clock::now();
    sample.start   = begin.time_since_epoch();
    sample.elapsed = time_point_cast<microseconds>(end).time_since_epoch() - time_point_cast<microseconds>(begin).time_since_epoch();
    session.addCpuSample(sample);
}

} // namespace clem