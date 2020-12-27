// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#ifndef CLEM_FACTOR_H_
#define CLEM_FACTOR_H_

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

	void           setPosition(const Point&);
	const Point&   getPosition() const;

	void           setTexture(const Texture&);
	const Texture& getTexture() const;

	void           addComponent(Component*);
	void           removeComponent(Component*);

protected:
	Point position;

private:
	Texture                 texture;
	std::vector<Component*> components;
};

#endif // CLEM_FACTOR_H_
