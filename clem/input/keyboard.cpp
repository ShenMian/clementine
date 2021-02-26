// Copyright 2020 SMS
// License(Apache-2.0)
// 键盘输入

#include "keyboard.h"
#include "clem/platform.h"


#ifdef OS_WIN

#include <windows.h>

void Keyboard::update()
{
  for(auto& pair : index)
		if(GetAsyncKeyState(static_cast<short>(pair.first)) & 0x8000)
      pair.second();
}

#endif // OS_WIN

