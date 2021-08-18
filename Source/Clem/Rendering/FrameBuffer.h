// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include <memory>

#include <string>
#include <unordered_map>

namespace clem
{

class FrameBuffer
{
public:
    static std::shared_ptr<FrameBuffer> create(Size2 size, int samples = 1);

    virtual void bind()   = 0;
    virtual void unbind() = 0;

    inline static std::unordered_map<std::string, std::shared_ptr<FrameBuffer>> map;
};

} // namespace clem