#include "Time.hpp"
// Copyright 2021 ShenMian
// License(Apache-2.0)

namespace core
{

inline constexpr float Time::asSeconds() const
{
	return static_cast<double>(microseconds_) / 1000000.0;
}

inline constexpr uint32_t Time::asMilliseconds() const
{
	return microseconds_ / 1000;
}

inline constexpr uint64_t Time::asMicroseconds() const
{
	return microseconds_;
}

inline constexpr Time Time::seconds(float sec)
{
	return Time(static_cast<uint64_t>(sec) * 1000000);
}

inline constexpr Time Time::milliseconds(uint32_t ms)
{
	return Time(static_cast<uint64_t>(ms) * 1000);
}

inline constexpr Time Time::microseconds(uint64_t us)
{
	return Time(us);
}

inline constexpr Time::Time(uint64_t us)
	: microseconds_(us)
{
}

}
