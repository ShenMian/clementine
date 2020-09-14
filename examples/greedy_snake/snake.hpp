// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_EXAMPLE_SNAKE_HPP_
#define CLEM_EXAMPLE_SNAKE_HPP_

#include <vector>
#include <clem/clem.hpp>

using std::vector;

class Snake : public Observer
{
public:
	Snake(Scene& scene)
	{
	}

	void onNotify(const Observable& o) override
	{
		const auto& input = dynamic_cast<const Input&>(o);
		for(auto& e : input.getEvents())		
		{
		}
	}

private:
}

#endif // CLEM_EXAMPLE_SNAKE_HPP_
