// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Trigger.h"
#include <Graphics.h>

namespace input
{

class KeyTrigger : public Trigger
{
public:
	KeyTrigger(Key key);

	bool isActuated() override;

private:
	Key key;
};

}
