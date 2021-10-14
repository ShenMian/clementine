// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

namespace clem
{

class CommandBuffer;

class CommandQueue
{
public:
    virtual void submit(CommandBuffer& cmdBuffer) = 0;
};

} // namespace clem