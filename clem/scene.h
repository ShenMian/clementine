// Copyright 2021 SMS
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

class Sprite;
class Rigidbody;

/// 场景, 管理游戏对象
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

	void addSprite(Sprite&);
	void removeSprite(Sprite&);
	void addRigidbody(Rigidbody&);
	void removeRigidbody(Rigidbody&);

	Scene(const Scene&) = delete;

private:
	void updateFactors(float dt);
	void updatePhysics(float dt);

	std::vector<Camera*> cameras;
	std::vector<Factor*> factors;

	std::vector<Sprite*>    sprites;
	std::vector<Rigidbody*> rigidbodies;
};

#endif // !CLEM_SCENE_H_
