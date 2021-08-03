// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Event.h"

class KeyPressEvent : public Event
{
public:
    EVENT_CLASS_TYPE(key_press);

    int key;

    KeyPressEvent(int key)
        : key(key)
    {
    }
};

class KeyReleaseEvent : public Event
{
public:
    EVENT_CLASS_TYPE(key_release);

    int key;

    KeyReleaseEvent(int key)
        : key(key)
    {
    }
};

class KeyRepeatEvent : public Event
{
public:
    EVENT_CLASS_TYPE(key_repeat);

    int key;

    KeyRepeatEvent(int key)
        : key(key)
    {
    }
};
