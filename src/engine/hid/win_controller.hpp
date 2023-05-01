// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "controller.hpp"

namespace hid
{

class WinController : public Controller
{
public:
	WinController(int index = 0);

	void        update() override;
	std::string name() const override;
	bool        connected() const override;
	void        vibration(float strong_speed, float weak_speed) override;

private:
	unsigned long index_;
};

} // namespace hid