// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Script.h"

namespace clem
{

class ScriptSystem : public System
{
public:
    void update(Time dt, Registry& reg)
    {
        reg.each<Script>([&](const Entity&, Script& script)
                         { script.onUpdate(dt); });
    }
};

} // namespace clem
