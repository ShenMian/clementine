// Copyright 2020 SMS
// License(Apache-2.0)
// ¹â±ê

typedef unsigned short ushort;
class Point;

class Cursor
{
public:
	static void moveTo(const Point& pos);
	static void moveTo(ushort x, ushort y);
  
	static void setVisible(bool);
};
