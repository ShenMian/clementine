// Copyright 2021 SMS
// License(Apache-2.0)
// 输入

#ifndef CLEM_INPUT_COMPONENT_H_
#define CLEM_INPUT_COMPONENT_H_

#include "clem/Component.h"

/// 输入组件
class InputComponent : public Component
{
public:
  virtual void update() = 0;
};

#endif // !CLEM_INPUT_COMPONENT_H_

