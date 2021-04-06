// Copyright 2021 SMS
// License(Apache-2.0)

#include "Transform.h"

namespace clem
{

const Point2& Transform::getPosition()
{
	return position;
}

const Point2& Transform::getLocalPosition()
{
	return localPosition;
}

void Transform::setLocalPosition(const Point2& p)
{
	dirty         = true;
	localPosition = p;

	// TODO
	position = localPosition;
}

} // namespace clem
