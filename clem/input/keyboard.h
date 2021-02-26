// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#ifndef CLEM_INPUT_KEYBOARD_H_
#define CLEM_INPUT_KEYBOARD_H_

#include <functional>
#include <unordered_map>

#include "input_component.h"

class Keyboard : public InputComponent
{
public:
  enum class Key;

  Keyboard();

  void bind(Key, std::function<void()>&);

private:
  std::unordered_map<Key, std::function<void()>> onPressed;
};

#endif // !CLEM_INPUT_KEYBOARD_H_

