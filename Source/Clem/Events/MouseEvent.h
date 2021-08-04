// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "Event.h"

namespace clem
{

/**
 * @brief 鼠标事件.
 */
class MouseEvent : public Event
{
public:
    EVENT_CLASS_TYPE(mouse);

    enum class Type
    {
        move,
        click,
        double_click,
        wheeled
    };

    enum class Key
    {
        left_buttom,
        right_buttom,
        none
    };

    MouseEvent(Type type, const Point2& pos, Key state = Key::none);

    Type          getType() const;
    const Point2& getPosition() const;
    Key           getKey() const;

private:
    Type   type;
    Point2 position;
    Key    key;
};

} // namespace clem