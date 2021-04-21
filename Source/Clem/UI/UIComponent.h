// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Math/Math.h"
#include "Clem/Rendering/Sprite.h"

namespace clem
{
// TODO: Entity, Sprite �Ľ��
class UIComponent : protected Sprite
{
public:
	void          setPosition(const Point2& p);
	const Point2& getPosition();

	void  setSize(const Size2 s);
	Size2 getSize() const;
};
} // namespace clem
