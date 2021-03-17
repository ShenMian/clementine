// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_MATH_SIZE_H_
#define CLEM_MATH_SIZE_H_

/**
 * @addtogroup Math
 * @{
 */

/**
 * ¶þÎ¬´óÐ¡.
 */
class Size
{
public:
	short x = 0;
	short y = 0;

	Size() = default;
	Size(short x, short y);

	short area() const;
};

/**
 * end of Math group
 * @}
 */

#endif // !CLEM_MATH_SIZE_H_
