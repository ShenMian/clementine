// Copyright 2021 SMS
// License(Apache-2.0)

#include "Profiler.h"
#include "Session.h"

namespace clem
{

Profiler& Profiler::get()
{
    static Profiler instance;
    return instance;
}

} // namespace clem