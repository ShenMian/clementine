// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <string_view>
#include <vector>

class ALCdevice;

namespace audio
{

/**
 * @brief 音频设备.
 */
class Device
{
public:
	Device(ALCdevice* handle);
	virtual ~Device();

	std::string_view getName() const;

	int getSampleRate() const;

	// static const std::vector<Device>& getOutputDevices();
	// static const std::vector<Device>& getInputDevices();

	static void init();
	static void deinit();

private:
	ALCdevice* handle;

	// inline static std::vector<Device> outputDevices;
	// inline static std::vector<Device> inputDevices;
};

} // namespace audio
