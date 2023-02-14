// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "unix_controller.hpp"
#include "core/platform.hpp"
#include <fcntl.h>
#include <linux/joystick.h>
#include <stdexcept>
#include <unistd.h>

namespace hid
{

using File = std::unique_ptr<int, decltype([](auto file) { close(file); })>;

#if TARGET_OS == OS_UNIX

UnixController::UnixController()
{
	file_ = (open("/dev/input/js1", O_RDONLY | O_NONBLOCK));
	if(file_.get() < 0)
		throw std::runtime_error("failed to open file");

	unsigned char axis_count   = 0;
	unsigned char button_count = 0;
	// ioctl(fd_, JSIOCGVERSION, &version);
	ioctl(file_.get(), JSIOCGAXES, &axis_count);
	ioctl(file_.get(), JSIOCGBUTTONS, &button_count);
}

void UnixController::update()
{
	js_event event;
	read(file_.get(), &event, sizeof(event));
	event.type &= ~JS_EVENT_INIT;
	switch(event.type)
	{
	case JS_EVENT_BUTTON:
		buttons_[event.number] = event.value;
		break;

	case JS_EVENT_AXIS:
		axis_[event.number] = event.value;
		break;
	}
}

std::string UnixController::name() const
{
	char name[128];
	ioctl(file_.get(), JSIOCGNAME(std::size(name), name);
	return name;
}

bool UnixController::connected() const
{
	return false; // TODO
}

void UnixController::vibration(float strong_speed, float weak_speed)
{
	core::check(0 <= strong_speed && strong_speed <= 1);
	core::check(0 <= weak_speed && weak_speed <= 1);

	ff_effect effect;
	effect.type                      = FF_RUMBLE;
	effect.u.rumble.strong_magnitude = strong_speed * std::numeric_limits<uint16_t>::max();
	effect.u.rumble.weak_magnitude   = weak_speed * std::numeric_limits<uint16_t>::max();
	effect.replay.length             = 1000;
	effect.replay.delay              = 0;
	effect.id                        = -1;
}

#endif

} // namespace hid