// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "UiComponent.h"
#include <string>

/**
 * @addtogroup Ui
 * @{
 */

class Text : public UiComponent
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
