// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <memory>

namespace clem
{

class FrameBuffer
{
public:
    static std::shared_ptr<FrameBuffer> create(Size2 size, int samples = 1);
};

} // namespace clem