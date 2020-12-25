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
	virtual ~Scene();

	void update();
	void render();

	void                        addFactor(Factor*);
	void                        removeFactor(Factor*);
	const std::vector<Factor*>& getFactors() const;

	void      addInput(Input* in);
	void      setPhysics(Physics* p);
	Physics*  getPhysics() const;

	void                        addCamera(Camera* cam);
	void                        removeCamera(Camera* cam);
	const std::vector<Camera*>& getCameras() const;
	Camera*                     getDefaultCamera() const;

private:
	void updateFactors();
	void updatePhysics();

	Camera*              defaultCamera;
	std::vector<Camera*> cameras;
	std::vector<Factor*> factors;
};

#endif // CLEM_SCENE_H_
