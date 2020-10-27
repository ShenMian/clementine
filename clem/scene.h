// Copyright 2020 SMS
// License(Apache-2.0)
// 场景

#ifndef CLEM_SCENE_H_
#define CLEM_SCENE_H_

#include <vector>
#include "type.h"

class Input;
class Camera;
class Factor;
class Physics;
class Renderer;

class Scene
{
public:
	Scene();
	Scene(const Size& size);
	virtual ~Scene();

	void update();
	void render(Renderer* renderer);

	void addFactor(Factor*);
	void removeFactor(Factor*);

	void      addInput(Input* in);
	void      setPhysics(Physics* p);
	Physics*  getPhysics() const;

	void                        addCamera(Camera* cam);
	void                        removeCamera(Camera* cam);
	const std::vector<Camera*>& getCameras() const;

private:
	void updateInput();
	void updatePhysics();

	Size size;
	std::vector<Input*>  inputs;
	Physics*             physics;
	Camera*              defaultCamera;
	std::vector<Camera*> cameras;
	std::vector<Factor*> factors;
};

#endif // CLEM_SCENE_H_
