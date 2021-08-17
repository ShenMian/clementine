﻿// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Browser.h"
#include "Dockspace.h"
#include "Hierarchy.h"
#include "Properties.h"
#include "Setting.h"

namespace clem
{

class WindowBase;

class UI
{
public:
    static void beginFrame();
    static void endFrame();

    static void init(WindowBase* window);
    static void deinit();
};

} // namespace clem