
#include "Component.h"

class Tile;
class Rect;
class Point;

class NSprite : public NComponent
{
public:
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
	 * @brief 设置可绘制区域的大小
	 */
	void setSize(Size s);

	/**
	 * @brief 获取可绘制区域的大小
	 */
	Size getSize() const;

	void onAdd() override;
	void onRemove() override;

private:
	Size              size;
	std::vector<Tile> buffer;
};
