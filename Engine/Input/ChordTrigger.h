// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Trigger.h"
#include <Graphics.h>
#include <vector>
#include <initializer_list>

namespace input
{

class ChordTrigger : public Trigger
{
public:
	ChordTrigger(std::initializer_list<Key> keys);

	bool isActuated() override;

private:
	// TODO: 使用掩码, 前提是 Key 不能是 enum class
	std::vector<Key> keys;
};

}
