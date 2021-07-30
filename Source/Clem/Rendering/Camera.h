// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include <memory>
#include <string>

namespace clem
{

class Camera
{
public:
	void setPosition(const Point3& pos);

	const Matrix4& getViewProjection() const;

private:
	Matrix4 projection;
	Matrix4 view;
	Matrix4 viewProjection;
};

} // namespace clem