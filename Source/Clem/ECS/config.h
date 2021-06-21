// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <cstdint>

typedef uint32_t EntityId;

constexpr auto chunkAlignment = 64;
constexpr auto chunkSize      = 16 * 1024;
