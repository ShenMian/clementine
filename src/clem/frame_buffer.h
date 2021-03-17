// Copyright 2021 SMS
// License(Apache-2.0)
// 帧缓冲区

#ifndef CLEM_FRAME_BUFFER_H_
#define CLEM_FRAME_BUFFER_H_

#include "platform.h"
#include "type.h"

class Tile;

/// 帧缓冲区
class FrameBuffer
{
#ifdef OS_WIN
	typedef CHAR_INFO buffer_t;
#else
  typedef Tile buffer_t;
#endif

public:
	/**
	 * @brief 构造函数.
	 */
	FrameBuffer() = default;

	/**
	 * @brief 析构函数.
	 */
	~FrameBuffer();
	
	/**
	 * @brief 绘制点.
	 * 
	 * @param x x坐标.
	 * @param y y坐标.
	 * @param t 瓦片.
	 */
	void drawPoint(int x, int y, const Tile& t);
	
	/**
	 * @brief 绘制点.
	 * 
	 * @param p 点的坐标.
	 * @param t 瓦片.
	 */
	void drawPoint(Point p, const Tile& t);

	/**
	 * @brief 绘制连接两点的直线.
	 * 
	 * @param a a点坐标.
	 * @param b b点坐标.
	 * @param t 瓦片.
	 */
	void drawLine(Point a, Point b, const Tile& t);
	
	/**
	 * @brief 绘制矩形.
	 * 
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void drawRect(Rect r, const Tile& t);

	/**
	 * @brief 绘制实心矩形.
	 * 
	 * @param r 矩形.
	 * @param t 瓦片.
	 */
	void fillRect(Rect r, const Tile& t);

	/**
	 * @brief 绘制圆形.
	 * 
	 * @param p 原点坐标.
	 * @param radius 半径.
	 * @param t 瓦片.
	 */
	void drawCycle(Point p, short radius, const Tile& t);
	
	/**
	 * @brief 清除全部绘制内容.
	 */
	void clear();

	/**
	 * @brief 交换缓冲区.
	 */
	void swapBuffers();
	
	void render();

	void setSize(Size);
	Size getSize() const;

private:
	buffer_t* current = nullptr;
	buffer_t* next    = nullptr;
	Size      size;
};

extern FrameBuffer frameBuffer;

#endif // !CLEM_FRAME_BUFFER_H_
