// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Core/Core.h"

namespace clem
{

class Layer
{
public:
	virtual void update(Time dt) = 0;
	virtual void attach();
	virtual void detach();
};

} // namespace clem