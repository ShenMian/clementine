// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "Panel.h"

class ViewportPanel : public Panel
{
public:
	void update() override;

	inline static bool visible = true;
};
