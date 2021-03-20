// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include "Clem/Math/Vec2.h"
#include "Clem/Platform.h"
#include "Sprite.h"
#include <vector>

class Rect;

#ifdef OS_UNIX
typedef Tile buffer_t;
#endif

#ifdef OS_WIN
typedef CHAR_INFO buffer_t;
#endif

class Framebuffer
{
public:
	void render();

	void drawSprite(const Point& positon, const Sprite& sprite);

	/**
	 * @brief ���Ƶ�.
	 * 
	 * @param x    x����.
	 * @param y    y����.
	 * @param tile ��Ƭ.
	 */
	void drawPoint(int x, int y, const Tile& tile);

	/**
	 * @brief ���Ƶ�.
	 * 
	 * @param p    �������.
	 * @param tile ��Ƭ.
	 */
	void drawPoint(const Point& p, const Tile& tile);

	/**
	 * @brief �������������ֱ��.
	 * 
	 * @param a    a������.
	 * @param b    b������.
	 * @param tile ��Ƭ.
	 */
	void drawLine(Point a, Point b, const Tile& tile);

	/**
	 * @brief ���ƾ���.
	 * 
	 * @param r    ����.
	 * @param tile ��Ƭ.
	 */
	void drawRect(Rect r, const Tile& tile);

	/**
	 * @brief ����ʵ�ľ���.
	 * 
	 * @param r    ����.
	 * @param tile ��Ƭ.
	 */
	void fillRect(Rect r, const Tile& tile);

	/**
	 * @brief ����Բ��.
	 * 
	 * @param p      ԭ������.
	 * @param radius �뾶.
	 * @param tile   ��Ƭ.
	 */
	void drawCycle(Point p, short radius, const Tile& tile);

	/**
	 * @brief ���ȫ����������.
	 */
	void clear();

	void        setSize(const Size&);
	const Size& getSize() const;

private:
	Size                  size;
	std::vector<buffer_t> buffer;
};

#endif // !CLEM_RENDERER_H_
