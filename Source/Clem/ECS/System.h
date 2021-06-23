// Copyright 2021 SMS
// License(Apache-2.0)

namespace clem
{

class System
{
public:
	virtual void update(float dt) = 0;

	virtual void init();
	virtual void deinit();
};

} // namespace clem
