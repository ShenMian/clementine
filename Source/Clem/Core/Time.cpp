// Copyright 2021 SMS
// License(Apache-2.0)

#include "Time.h"
#include "Core/Assert.hpp"
#include <limits>

namespace clem
{

Time::Time(uint64_t us)
    : microseconds_(us)
{
}

[[nodiscard]] float Time::seconds() const
{
    return (microseconds_ / 1000000.f);
}

[[nodiscard]] uint32_t Time::milliseconds() const
{
    return static_cast<uint32_t>(microseconds_) / 1000;
}

[[nodiscard]] uint64_t Time::microseconds() const
{
    return microseconds_;
}

[[nodiscard]] Time Time::seconds(float sec)
{
    Assert::isTrue(sec < 0, "cannot be negative");
    Assert::isTrue(sec <= std::numeric_limits<uint64_t>::max() / 1000000, "overflow");
    return Time(static_cast<uint64_t>(sec) * 1000000);
}

[[nodiscard]] Time Time::milliseconds(uint32_t ms)
{
    return Time(static_cast<uint64_t>(ms) * 1000);
}

[[nodiscard]] Time Time::microseconds(uint64_t us)
{
    return Time(us);
}

} // namespace clem