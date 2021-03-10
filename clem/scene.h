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

	void update(float dt);
	void render();

	void                        addFactor(Factor&);
	void                        removeFactor(Factor&);
	const std::vector<Factor*>& getFactors() const;

	void                        addCamera(Camera& cam);
	void                        removeCamera(Camera& cam);
  const std::vector<Camera*>& getCameras() const;
	Camera*                     getDefaultCamera() const;

	Scene(const Scene&) = delete;

private:
	void updateFactors(float dt);
	void updatePhysics(float dt);

	Camera*              defaultCamera;
	std::vector<Camera*> cameras;
	std::vector<Factor*> factors;
};

#endif // !CLEM_SCENE_H_
