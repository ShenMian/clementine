// Copyright 2021 SMS
// License(Apache-2.0)

#include "Time.h"

namespace clem
{

Time::Time(uint64_t us)
		: microseconds_(us)
{
}

float Time::seconds() const
{
	return (microseconds_ / 1000000.0f);
}

uint32_t Time::milliseconds() const
{
	return static_cast<uint32_t>(microseconds_) / 1000;
}

uint64_t Time::microseconds() const
{
	return microseconds_;
}

Time seconds(float sec)
{
	return Time(static_cast<uint64_t>(sec * 1000000));
}

Time milliseconds(uint32_t ms)
{
	return Time(static_cast<uint64_t>(ms * 1000));
}

Time microseconds(uint64_t us)
{
	return Time(us);
}

} // namespace clem
