// Copyright 2020 SMS
// License(Apache-2.0)
// 矩形

#ifndef CLEM_TYPE_RECT_H_
#define CLEM_TYPE_RECT_H_

class Size;
class Point;

class Rect
{
public:
	Rect();
	Rect(const Point& p, const Size& size);
	Rect(float x, float y, float width, float height);

	float top() const;
	float bottom() const;
	float left() const;
	float right() const;

	Point tl() const;
	Point tr() const;
	Point bl() const;
	Point br() const;

	Size  size() const;
	Point center() const;
	float area() const;

	Rect intsect(const Rect&) const;
	bool contains(const Point&) const;
	bool contains(const Rect&) const;

public:
	float x;
	float y;
	float width;
	float height;
};

#endif // CLEM_TYPE_RECT_H_
