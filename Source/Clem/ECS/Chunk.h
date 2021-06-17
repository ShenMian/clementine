// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <array>

struct alignas(chunkAlignment) Chunk
{
public:
	std::array<std::byte, chunkSize> buffer;
};
