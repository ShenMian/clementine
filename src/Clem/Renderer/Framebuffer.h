// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_RENDERER_H_
#define CLEM_RENDERER_H_

#include "Clem/Core/Math/Rect2.h"
#include "Clem/Core/Math/Vector2i.h"
#include "Clem/Platform.h"
#include "Sprite.h"
#include <vector>

#ifdef OS_UNIX
typedef Tile buffer_t;
#endif

#ifdef OS_WIN
typedef CHAR_INFO buffer_t;
#endif

class Framebuffer
{
public:
	void output();

	void drawSprite(const Point2i& positon, const Sprite& sprite);

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
	void drawPoint(const Point2i& p, const Tile& tile);

	/**
	 * @brief �������������ֱ��.
	 *
	 * @param a    a������.
	 * @param b    b������.
	 * @param tile ��Ƭ.
	 */
	void drawLine(Point2i a, Point2i b, const Tile& tile);

	/**
	 * @brief ���ƾ���.
	 *
	 * @param r    ����.
	 * @param tile ��Ƭ.
	 */
	void drawRect(Rect2i r, const Tile& tile);

	/**
	 * @brief ����ʵ�ľ���.
	 *
	 * @param r    ����.
	 * @param tile ��Ƭ.
	 */
	void fillRect(Rect2i r, const Tile& tile);

	/**
	 * @brief ����Բ��.
	 *
	 * @param p      ԭ������.
	 * @param radius �뾶.
	 * @param tile   ��Ƭ.
	 */
	void drawCycle(Point2i p, short radius, const Tile& tile);

	/**
	 * @brief �����ַ���.
	 *
	 * @param pos ��������λ��
	 * @param str Ҫ���Ƶ��ַ���
	 */
	void drawString(const Point2i& pos, std::wstring str);

	/**
	 * @brief ���ȫ����������.
	 */
	void clear(const Tile& = Tile::blank);

	void          setSize(const Size2i&);
	const Size2i& getSize() const;

private:
	Size2i                size;
	std::vector<buffer_t> buffer;
};

#endif // !CLEM_RENDERER_H_
