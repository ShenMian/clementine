// Copyright 2021 SMS
// License(Apache-2.0)
// 键盘输入

#ifndef CLEM_INPUT_CONTROLLER_H_
#define CLEM_INPUT_CONTROLLER_H_

#include "input_component.h"

/// 游戏控制器
class Controller : public InputComponent
{
public:
  Controller();

  void update() override;

private:
};

#endif // !CLEM_INPUT_CONTROLLER_H_

