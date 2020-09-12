// Copyright 2020 SMS
// License(Apache-2.0)
// ³¡¾°ÉãÏñ»ú

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
	Camera(Scene& scene);

  void render(Renderer& renderer, const std::vector<Entity*>& objs);

	void setInputRect(const Rect& rect);
	void setOutputRect(const Rect& rect);

private:
	bool inSight(const Entity& obj) const;

	Rect   inputRect;
	Rect   outputRect;
	Scene& scene;
  ushort depth;
};

#endif // CLEM_CAMERA_H_
