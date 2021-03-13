// Copyright 2021 SMS
// License(Apache-2.0)
// 鼠标输入

#ifndef CLEM_INPUT_MOUSE_H_
#define CLEM_INPUT_MOUSE_H_

#include "input_component.h"
#include <functional>

/// 鼠标输入
class Mouse : public InputComponent
{
public:
  Mouse();

  void update() override;

private:
};

#endif // !CLEM_INPUT_MOUSE_H_

