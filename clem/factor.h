// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#ifndef CLEM_FACTOR_H_
#define CLEM_FACTOR_H_

#include "texture.h"
#include <vector>

class Scene;
class Physics;
class Component;

class Factor
{
public:
	Factor();
	Factor(const Size&);
	Factor(const Texture&);

	virtual void update();

	void         setPosition(const Point&);
	const Point& getPosition() const;

	void     setTexture(const Texture&);
	Texture& getTexture();

	void addComponent(Component*);
	void removeComponent(Component*);

protected:
	Point position;

private:
	Texture                 texture;
	std::vector<Component*> components;
};

#endif // CLEM_FACTOR_H_
