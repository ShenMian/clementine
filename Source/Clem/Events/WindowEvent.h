// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "Event.h"

/**
 * @brief 窗体事件.
 */
class WindowEvent : public Event
{
public:
    EVENT_CLASS_TYPE(window);

    enum class Type
    {
        move,
        resize
    };

    WindowEvent(Type type);

    Type getType() const;

private:
    Type type;
};
