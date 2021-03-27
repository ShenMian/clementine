// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_COMPONENT_TRANSFORM_H_
#define CLEM_COMPONENT_TRANSFORM_H_

#include "Clem/Component/Component.h"
#include "Clem/Core/Math/Math.h"

class Transform : public Component
{
public:
	const Point2& getPosition();

	const Point2& getLocalPosition();
	void          setLocalPosition(const Point2&);

private:
	Vector2    localPosition;
	Vector2    position;
	Transform* parent = nullptr;
	bool       dirty  = true;
};

#endif // !CLEM_COMPONENT_TRANSFORM_H_
