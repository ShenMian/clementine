// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_EXAMPLE_SNAKE_HPP_
#define CLEM_EXAMPLE_SNAKE_HPP_

#include <vector>
#include <clem/clem.hpp>

using std::vector;

const int len = 2;

class Snake : public Factor
{
public:
	Snake()
	{
		int x, y;
		assert(y >= len);
		for(int i = 0; i < len; i++)
		{
			auto f = new Factor(Texture());
			f->setTexture(Tile('#'));
			f->setPosition(Point(x, y - i));
			body.push_back(f);
		}
	}

	~Snake()
	{
		for(auto f : body)
			delete f;
	}

	void update() override
	{
		
	}

	void increaseBody()
	{
		
	}

private:
	vector<Factor*> body;
};

#endif // CLEM_EXAMPLE_SNAKE_HPP_
