// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "UIComponent.h"
#include <string>

/**
 * @addtogroup Ui
 * @{
 */

class Text : public UIComponent
{
public:
	void setText(std::wstring_view t, Color c = Color());

private:
	std::wstring text;
	Color        color;
};

/**
 * end of Ui group
 * @}
 */
