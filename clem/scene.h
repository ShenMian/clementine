// Copyright 2020 SMS
// License(Apache-2.0)
// 场景

#ifndef CLEM_SCENE_H_
#define CLEM_SCENE_H_

#include <vector>
#include "type.h"

class Input;
class Camera;
class Entity;
class Physics;
class Renderer;

class Scene
{
public:
	Scene();
	Scene(const Size& size);

	void update();
	void render();

	void addEntity(Entity*);
	void removeEntity(Entity*);

	void      addInput(Input* in);
	void      setPhysics(Physics* p);
	Physics*  getPhysics() const;
	void      setRenderer(Renderer* r);
	Renderer* getRenderer() const;

	void                        addCamera(Camera* cam);
	void                        removeCamera(Camera* cam);
	const std::vector<Camera*>& getCameras() const;

private:
	void updateInput();
	void updatePhysics();

	Size size;
	std::vector<Input*>  inputs;
	Physics*             physics;
	Renderer*            renderer;
	std::vector<Camera*> cameras;
	std::vector<Entity*> entitys;
};

#endif // CLEM_SCENE_H_
