
typedef unsigned short ushort;
class Point;

class Cursor
{
public:
	void moveTo(const Point& pos) const;
	void moveTo(ushort x, ushort y) const;

	static void moveUp(ushort n);
	static void moveDown(ushort n);
	static void moveRight(ushort n);
	static void moveLeft(ushort n);
  
	void setVisible(bool) const;

	static void show();
  static void hide();
};

