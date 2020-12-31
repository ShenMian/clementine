
typedef unsigned short ushort;
class Point;

class Cursor
{
public:
	static void moveTo(const Point& pos);
	static void moveTo(ushort x, ushort y);
  
	static void setVisible(bool);
};

/*
	static void moveUp(ushort n);
	static void moveDown(ushort n);
	static void moveRight(ushort n);
	static void moveLeft(ushort n);
*/
