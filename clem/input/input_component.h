// Copyright 2020 SMS
// License(Apache-2.0)
// 输入

#ifndef CLEM_INPUT_COMPONENT_H_
#define CLEM_INPUT_COMPONENT_H_

#include "clem/component.h"

class InputComponent : public Component
{
public:
  InputComponent();

  virtual void update() = 0;
};

#endif // !CLEM_INPUT_COMPONENT_H_

