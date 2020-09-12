// Copyright 2020 SMS
// License(Apache-2.0)
// ¾ØÐÎ

#ifndef CLEM_TYPE_RECT_HPP_
#define CLEM_TYPE_RECT_HPP_

class Size;
class Vector;

typedef unsigned short ushort;

class Rect
{
public:
	float x;
	float y;
	float width;
	float height;

	float right() const;
	float bottom() const;

	Rect();
	Rect(const Vector& vec, const Size& size);
	Rect(ushort x, ushort y, ushort width, ushort height);
};

#endif // CLEM_TYPE_RECT_HPP_
