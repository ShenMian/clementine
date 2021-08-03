// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Core.h"
#include "ECS/ECS.h"

namespace clem
{

class System
{
public:
    virtual void update(Time dt, Registry& reg) = 0;

    virtual void init();
    virtual void deinit();
};

} // namespace clem
