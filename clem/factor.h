// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#ifndef CLEM_FACTOR_H_
#define CLEM_FACTOR_H_

#include "scene.h"
#include <vector>

class Physics;
class Collider;
class Component;

class Factor
{
public:
	Factor();
	Factor(Scene&);
	Factor(const Size&);

	virtual void update(float dt);

	void         setPosition(const Point&);
	const Point& getPosition() const;

	void addComponent(Component&);
	void removeComponent(Component&);

	void   setScene(Scene*);
	Scene* getScene() const;

	virtual void onCollision(Collider, Collider);

protected:
	Point position;

private:
	Scene*                  scene;
	std::vector<Component*> components;
};

#endif // !CLEM_FACTOR_H_
