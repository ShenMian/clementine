// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <array>
#include <cstddef>

constexpr auto chunkAlignment = 64;
constexpr auto chunkSize      = 16 * 1024;

struct alignas(chunkAlignment) Chunk
{
	static constexpr size_t size = chunkSize;

private:
	std::array<std::byte, size> buffer;
};
