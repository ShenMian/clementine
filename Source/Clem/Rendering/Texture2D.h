// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <filesystem>
#include <memory>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Texture2D
{
public:
    static std::shared_ptr<Texture2D> create(const std::filesystem::path& path);

    virtual Size2i getSize() const = 0;
    virtual void*  getHandle()     = 0;

    virtual void bind(unsigned int slot) = 0;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem
