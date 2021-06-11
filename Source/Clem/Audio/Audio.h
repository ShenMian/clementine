// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Listener.h"
#include "Sound.h"
#include "Source.h"
#include "AL/alext.h"

namespace clem
{
/**
 * @addtogroup Audio
 * @{
 */

class Audio
{
public:
	static void init();
	static void deinit();

	Audio() = delete;

private:
	static ALCdevice*  device;
	static ALCcontext* context;
};

/**
 * end of Audio group
 * @}
 */
} // namespace clem
