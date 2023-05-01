// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "win_controller.hpp"
#include "controller.hpp"
#include "core/check.hpp"
#include "core/platform.hpp"
#include <optional>
#include <stdexcept>

#include <bitset>

#if TARGET_OS == OS_WIN

	#include <Windows.h>
	#include <Xinput.h>

namespace
{

template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept
{
	return static_cast<typename std::underlying_type<E>::type>(e);
}

typedef struct _XINPUT_CAPABILITIES_EX
{
	XINPUT_CAPABILITIES Capabilities;
	WORD                VendorId;
	WORD                ProductId;
	WORD                VersionNumber;
	WORD                unk1;
	DWORD               unk2;
} XINPUT_CAPABILITIES_EX, *PXINPUT_CAPABILITIES_EX;

DWORD XInputGetCapabilitiesEx(DWORD dwUserIndex, PXINPUT_CAPABILITIES_EX pCapabilitiesEx)
{
	DWORD(WINAPI * XInputGetCapabilitiesExFunc)
	(DWORD unk1, DWORD dwUserIndex, DWORD dwFlags, PXINPUT_CAPABILITIES_EX pCapabilities);
	XInputGetCapabilitiesExFunc = reinterpret_cast<decltype(XInputGetCapabilitiesExFunc)>(
	    ::GetProcAddress(::GetModuleHandleW(L"XInput1_4.dll"), (LPCSTR)108));

	if(!XInputGetCapabilitiesExFunc)
		return ERROR_INVALID_FUNCTION;

	return XInputGetCapabilitiesExFunc(1, dwUserIndex, 0, pCapabilitiesEx);
}

std::optional<XINPUT_CAPABILITIES_EX> GetCapabilitiesEx(DWORD index)
{
	XINPUT_CAPABILITIES_EX capabilities;
	if(XInputGetCapabilitiesEx(index, &capabilities) != ERROR_SUCCESS)
		return std::nullopt;
	return capabilities;
}

std::optional<XINPUT_BATTERY_INFORMATION> GetBatteryInformation(DWORD index)
{
	XINPUT_BATTERY_INFORMATION info;
	if(XInputGetBatteryInformation(index, BATTERY_DEVTYPE_GAMEPAD, &info) != ERROR_SUCCESS)
		return std::nullopt;
	return info;
}

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

} // namespace

namespace hid
{

WinController::WinController(int index) : index_(index)
{
}

void WinController::update()
{
	const auto state = GetState(index_).value();

	// FIXME: remap buttons
	buttons_ = state.Gamepad.wButtons;

	axes_[to_underlying(Thumb::leftX)]  = state.Gamepad.sThumbLX;
	axes_[to_underlying(Thumb::leftY)]  = state.Gamepad.sThumbLY;
	axes_[to_underlying(Thumb::rightX)] = state.Gamepad.sThumbRX;
	axes_[to_underlying(Thumb::rightY)] = state.Gamepad.sThumbRY;

	axes_[to_underlying(Trigger::left)]  = state.Gamepad.bLeftTrigger;
	axes_[to_underlying(Trigger::right)] = state.Gamepad.bRightTrigger;
}

std::string WinController::name() const
{
	const auto caps = GetCapabilitiesEx(index_).value();

	// TODO: 通过 VendorId 和 ProductId 查询手柄类型, 表格: https://github.com/libsdl-org/SDL/blob/main/src/joystick/controller_type.c

	return std::string();
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
