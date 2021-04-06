// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include "Clem/Core/Math/Math.h"

/**
 * @brief 听者.
 */
class Listener
{
public:
	typedef ALuint id_t;

	void setPosition(const Point2& p);
	void setVelocity(const Vector2& v);
	
private:
	id_t id;
};
