// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_CURSOR_H_
#define CLEM_RENDERER_CURSOR_H_

#include "Clem/Core/Math/Vector2f.h"

/**
 * @brief 光标.
 */
class Cursor
{
public:
  /**
   * @brief 移动光标到指定坐标
   * 
   * @param p 坐标
   */
  static void move(const Point2& p);
  
  /**
   * @brief 移动光标到指定坐标
   * 
   * @param x x坐标
   * @param y y坐标
   */
	static void move(short x, short y);

  /**
   * @brief 设置光标可见性
   * 
   * @param v 可见性
   */
	static void setVisible(bool v);
};

#endif // !CLEM_RENDERER_CURSOR_H_
