#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

#include <fcntl.h>
#include <linux/joystick.h>
#include <unistd.h>

#include <iostream>

class Controller
{
public:
	Controller()
	{
		if((file_ = open("/dev/input/js1", O_RDONLY | O_NONBLOCK)) < 0)
		{
			return;
		}

		char          name[128];
		unsigned char axis_count   = 0;
		unsigned char button_count = 0;
		// ioctl(fd_, JSIOCGVERSION, &version);
		ioctl(file_, JSIOCGAXES, &axis_count);
		ioctl(file_, JSIOCGBUTTONS, &button_count);
		ioctl(file_, JSIOCGNAME(128), name);

		std::cout << "name        : " << name << '\n';
		std::cout << "axis count  : " << (int)axis_count << '\n';
		std::cout << "button count: " << (int)button_count << '\n';
	}

	virtual ~Controller() { close(file_); }

	void update()
	{
		js_event event;
		read(file_, &event, sizeof(event));
		switch(event.type)
		{
		case JS_EVENT_BUTTON:
			std::cout << "button event\n";
			break;

		case JS_EVENT_AXIS:
			std::cout << "axis event\n";
			break;

		case JS_EVENT_INIT:
			std::cout << "init event\n";
			break;
		}
	}

	void vibration(uint16_t strong, uint16_t weak)
	{
		ff_effect effect;
		effect.type                      = FF_RUMBLE;
		effect.u.rumble.strong_magnitude = 65535;
		effect.u.rumble.weak_magnitude   = 65535;
		effect.replay.length             = 1000;
		effect.replay.delay              = 0;
		effect.id                        = -1;
	}

private:
	int file_;
};
