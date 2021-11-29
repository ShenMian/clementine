// Copyright 2021 ShenMian
// License(Apache-2.0)

#include <string>

class Achievement
{
public:
	std::string name;
	bool        locked;

	void unlock();

	static void init();
};
