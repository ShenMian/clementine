// Copyright 2020 SMS
// License(Apache-2.0)
// 游戏对象

#ifndef CLEM_FACTOR_H_
#define CLEM_FACTOR_H_

#include "scene.h"
#include "texture.h"
#include <vector>

class Physics;
class Component;

class Factor
{
public:
	Factor();
	Factor(const Size&);
	Factor(const Texture&);

	virtual void update(float dt);

	void         setPosition(const Point&);
	const Point& getPosition() const;

	void setVelocity(const Vec2&);

	void     setTexture(const Texture&);
	Texture& getTexture();

	void addComponent(Component&);
	void removeComponent(Component&);

	void   setScene(Scene*);
	Scene* getScene() const;

protected:
	Point position;
	Vec2  velocity;

private:
	Scene*                  scene;
	Texture                 texture;
	std::vector<Component*> components;
};

#endif // !CLEM_FACTOR_H_
