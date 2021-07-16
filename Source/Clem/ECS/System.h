// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

namespace clem
{

class Registry;

class System
{
public:
	virtual void update(float dt, Registry& reg) = 0;

	virtual void init();
	virtual void deinit();
};

} // namespace clem
