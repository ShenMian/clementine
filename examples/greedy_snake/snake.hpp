// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_EXAMPLE_SNAKE_HPP_
#define CLEM_EXAMPLE_SNAKE_HPP_

#include <vector>
#include <clem/clem.hpp>

using std::vector;
using Attr = Attribute;

class Snake : public Entity
{
public:
	Snake(Scene& scene)
			: Entity(scene, {'@', Attr(fore::green)}),
				fruit(scene, {'*', Attr(fore::red)}),
				border({0, 0}, Terminal::getWindowSize())
	{
		generate();
	}

	void update() override
	{
		auto lastPos = getPosition();
		Entity::update();
		auto pos = getPosition();
		pos      = Vector((int)pos.x, (int)pos.y);

		// 碰撞检测
		if(pos.x < border.x || pos.x > border.width ||
			 pos.y < border.y || pos.y > border.height)
			assert(false);
		
		if(pos == fruit.getPosition())
			generate();

		if(Vector((int)pos.x, (int)pos.y) != Vector((int)lastPos.x, (int)lastPos.y))
			bodys.back()->setPosition(lastPos);

		// 身体随头部移动
		for(size_t i = 0; i + 1 < bodys.size(); i++)
			bodys[i]->setPosition(bodys[i + 1]->getPosition());
	}

	~Snake()
	{
		for(auto body : bodys)
			delete body;
	}

	void generate()
	{
		auto x = rand() % (int)border.width + (int)border.x;
		auto y = rand() % (int)border.height + (int)border.y;
		fruit.setPosition(Vector(x, y));
		bodys.push_back(new Entity(getScene(), {'#', Attr(fore::green)}));
	}

private:
	Rect                border;
	vector<Entity*> bodys;
	Entity          fruit;
};

#endif // CLEM_EXAMPLE_SNAKE_HPP_
