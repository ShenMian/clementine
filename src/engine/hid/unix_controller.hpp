// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "controller.hpp"
#include <memory>

#if TARGET_OS == OS_UNIX
	#include <unistd.h>
#endif

namespace hid
{

#if TARGET_OS == OS_UNIX
using File = std::unique_ptr<int, decltype([](auto file) { close(*file); })>;
#endif

class UnixController : public Controller
{
public:
	UnixController(int index = 0);

	void        update() override;
	std::string name() const override;
	bool        connected() const override;
	void        vibration(float strong_speed, float weak_speed) override;

private:
	int          index_;
	mutable File input_;
	File         output_;
	bool         playing_ = false;
};

} // namespace hid
