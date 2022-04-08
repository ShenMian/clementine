// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <functional>

namespace input
{

/**
 * @brief 触发器.
 *
 * 用于检测指定状态是否满足, 若满足则触发对应行为. 因为可能存在状态, 所以作为类, 而不是简单的函数.
 */
class Trigger
{
public:
	virtual bool isActuated() = 0;
};

}
