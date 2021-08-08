// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <typeindex>

namespace clem
{

using id_type      = uint32_t;
using version_type = uint16_t;

static_assert(std::is_integral<id_type>::value, "id_type must be integral.");
static_assert(std::is_integral<version_type>::value, "version_type must be integral.");

constexpr size_t chunk_alignment = 64;
constexpr size_t chunk_size      = 16 * 1024;

} // namespace clem