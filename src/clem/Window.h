// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_WINDOW_H_
#define CLEM_WINDOW_H_

#include "Clem/Math.h"
#include <string>

class Window
{
public:
  static Size getSize();
  static void setTitle(std::string& title);
};

#endif // !CLEM_WINDOW_H_
