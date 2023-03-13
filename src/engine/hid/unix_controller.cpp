// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "unix_controller.hpp"
#include "core/check.hpp"
#include <filesystem>
#include <stdexcept>

#include <fmt/color.h>
#include <fmt/format.h>

#if TARGET_OS == OS_UNIX

	#include <fcntl.h>
	#include <linux/joystick.h>

	#define BITS_TO_LONGS(x) (((x) + 8 * sizeof(unsigned long) - 1) / (8 * sizeof(unsigned long)))

namespace hid
{

UnixController::UnixController(int index) : index_(index)
{
	input_.reset(new int(open(fmt::format("/dev/input/js{}", index_).c_str(), O_RDONLY | O_NONBLOCK)));
	if(*input_.get() == -1)
		throw std::runtime_error("failed to open file");

	unsigned char axis_count   = 0;
	unsigned char button_count = 0;
	// ioctl(fd_, JSIOCGVERSION, &version);
	ioctl(*input_.get(), JSIOCGAXES, &axis_count);
	ioctl(*input_.get(), JSIOCGBUTTONS, &button_count);

	for(int i = 0; i <= 99; i++)
	{
		if(std::filesystem::exists(fmt::format("/sys/class/input/js{}/device/event{}", index_, i)))
		{
			output_.reset(new int(open(fmt::format("/dev/input/event{}", i).c_str(), O_RDWR)));
			break;
		}
	}
	CLEM_DEBUG_CHECK(output_.get() != nullptr && *output_.get() != -1);
}

void UnixController::update()
{
	js_event event;
	read(*input_.get(), &event, sizeof(event));
	event.type &= ~JS_EVENT_INIT;
	switch(event.type)
	{
	case JS_EVENT_BUTTON:
		buttons_[event.number] = event.value;
		break;

	case JS_EVENT_AXIS:
		axes_[event.number] = event.value;
		break;
	}
}

std::string UnixController::name() const
{
	char name[128];
	ioctl(*input_.get(), JSIOCGNAME(std::size(name)), name);
	return name;
}

bool UnixController::connected() const
{
	input_.reset(new int(open(fmt::format("/dev/input/js{}", index_).c_str(), O_RDONLY | O_NONBLOCK)));
	return *input_.get() != -1;
}

void UnixController::vibration(float strong_speed, float weak_speed)
{
	CLEM_DEBUG_CHECK(0.f <= strong_speed && strong_speed <= 1.f);
	CLEM_DEBUG_CHECK(0.f <= weak_speed && weak_speed <= 1.f);

	unsigned long features[BITS_TO_LONGS(FF_CNT)];
	if(ioctl(*output_.get(), EVIOCGBIT(EV_FF, sizeof(features)), features) == -1)
		throw std::runtime_error("failed to get features");

	if(playing_)
	{
		// FIXME
		input_event stop_event;
		stop_event.type  = EV_FF;
		stop_event.code  = -1;
		stop_event.value = 1;
		if(write(*output_.get(), &stop_event, sizeof(stop_event)) == -1)
			throw std::runtime_error("failed to stop effect");

		if(ioctl(*output_.get(), EVIOCRMFF, 0) == -1) // FIXME: effect.id
			throw std::runtime_error("failed to remove effect");

		playing_ = false;
	}

	if(strong_speed == 0 && weak_speed == 0)
		return;

	ff_effect effect;
	effect.type                      = FF_RUMBLE;
	effect.u.rumble.strong_magnitude = strong_speed * std::numeric_limits<uint16_t>::max();
	effect.u.rumble.weak_magnitude   = weak_speed * std::numeric_limits<uint16_t>::max();
	effect.replay.length             = -1;
	effect.replay.delay              = 0;
	effect.id                        = -1;
	if(ioctl(*output_.get(), EVIOCSFF, &effect) == -1)
		throw std::runtime_error("failed to upload effect");

	input_event play_event;
	play_event.type  = EV_FF;
	play_event.code  = effect.id;
	play_event.value = 1;
	if(write(*output_.get(), &play_event, sizeof(play_event)) == -1)
		throw std::runtime_error("failed to play effect");

	playing_ = true;
}

} // namespace hid

#endif
