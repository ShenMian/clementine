// Copyright 2020 SMS
// License(Apache-2.0)
// 大小

#ifndef CLEM_TYPE_SIZE_H_
#define CLEM_TYPE_SIZE_H_

typedef unsigned short ushort;

class Size
{
public:
	ushort x;
	ushort y;

	ushort area() const;

	Size operator+(const Size& size) const;

	Size();
	Size(int x, int y);
};

#endif // CLEM_TYPE_SIZE_H_
