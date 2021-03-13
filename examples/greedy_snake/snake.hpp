// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_EXAMPLE_SNAKE_HPP_
#define CLEM_EXAMPLE_SNAKE_HPP_

#include <vector>
#include <cassert>
#include "clem/clem.hpp"

using std::vector;

const int len = 2;

class Snake : public Factor
{
public:
	Snake()
	{
	}

	~Snake()
	{
	}

	void update() override
	{
	}

	void increaseBody()
	{
	}
private:
};

#endif // CLEM_EXAMPLE_SNAKE_HPP_
