// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#ifndef CLEM_GAME_OBJECT_H_
#define CLEM_GAME_OBJECT_H_

#include <vector>
#include "texture.h"

class Scene;
class Physics;
class Component;

class Factor
{
public:
	Factor();
	Factor(const Texture& texture);

	virtual void update();

	void addComponent(Component* com);
	void removeComponent(Component* com);

	void           setPosition(const Point& pos);
	const Point&   getPosition() const;
	void           setTexture(const Texture& texture);
	const Texture& getTexture() const;

	Scene& getScene() const;

private:
	std::vector<Component*> components;

	Point   position;
	Texture texture;
};

#endif // CLEM_GAME_OBJECT_H_
