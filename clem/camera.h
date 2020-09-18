// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#ifndef CLEM_CAMERA_H_
#define CLEM_CAMERA_H_

#include <vector>
#include "type.h"

class Scene;
class Renderer;
class Entity;

class Camera
{
public:
	Camera();

	void render();
  void render(const std::vector<Entity*>& objs);

	void setScene(Scene* s);
	void setRenderer(Renderer* r);

	void   setDepth(ushort depth);
	ushort getDepth() const;

	void setInputRect(const Rect& rect);
	void setOutputRect(const Rect& rect);

private:
	bool inSight(const Entity& obj) const;

	Rect      inputRect;
	Rect      outputRect;
	Scene*    scene;
	Renderer* renderer;
  ushort    depth;
};

#endif // CLEM_CAMERA_H_
