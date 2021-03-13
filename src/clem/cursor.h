// Copyright 2021 SMS
// License(Apache-2.0)
// 光标

class Point;

/// 光标, 控制光标移动和设置相关属性
class Cursor
{
public:
	static void move(const Point& pos);
	static void move(short x, short y);
  
	static void setVisible(bool);
};
