// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "win_controller.hpp"
#include "controller.hpp"
#include "core/platform.hpp"
#include "core/check.hpp"
#include <optional>
#include <stdexcept>

#if TARGET_OS == OS_WIN

	#include <Windows.h>
	#include <Xinput.h>

namespace hid
{

std::optional<XINPUT_CAPABILITIES> GetCapabilities(DWORD index)
{
	XINPUT_CAPABILITIES capabilities;
	if(XInputGetCapabilities(index, 0, &capabilities) != ERROR_SUCCESS)
		return std::nullopt;
	return capabilities;
}

std::optional<XINPUT_STATE> GetState(int index)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	if(XInputGetState(index, &state) != ERROR_SUCCESS)
		return std::nullopt;
	return state;
}

void WinController::update()
{
	const auto state = GetState(index_).value();

	buttons_ = state.Gamepad.wButtons;

	axes_[static_cast<uint8_t>(Thumb::left)]      = state.Gamepad.sThumbLX;
	axes_[static_cast<uint8_t>(Thumb::left) + 1]  = state.Gamepad.sThumbLY;
	axes_[static_cast<uint8_t>(Thumb::right)]     = state.Gamepad.sThumbRX;
	axes_[static_cast<uint8_t>(Thumb::right) + 1] = state.Gamepad.sThumbRY;

	axes_[static_cast<uint8_t>(Trigger::left)]  = state.Gamepad.bLeftTrigger;
	axes_[static_cast<uint8_t>(Trigger::right)] = state.Gamepad.bRightTrigger;
}

std::string WinController::name() const
{
	return std::string(); // TODO: https://gist.github.com/DJm00n/0f0563702f6cf01e8812ebc760a78cf1
}

bool WinController::connected() const
{
	XINPUT_STATE state;
	return XInputGetState(index_, &state) == ERROR_SUCCESS;
}

void WinController::vibration(float strong_speed, float weak_speed)
{
	CLEM_DEBUG_CHECK(0.f <= strong_speed && strong_speed <= 1.f);
	CLEM_DEBUG_CHECK(0.f <= weak_speed && weak_speed <= 1.f);

	if(!connected())
		return;

	XINPUT_VIBRATION state = {};
	state.wLeftMotorSpeed  = strong_speed * std::numeric_limits<WORD>::max();
	state.wRightMotorSpeed = weak_speed * std::numeric_limits<WORD>::max();
	if(XInputSetState(index_, &state) != ERROR_SUCCESS && connected())
		throw std::runtime_error("failed to set vibration");
}

} // namespace hid

#endif
