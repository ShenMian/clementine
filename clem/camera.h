// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#ifndef CLEM_CAMERA_H_
#define CLEM_CAMERA_H_

#include <vector>
#include "type.h"

class Scene;
class Renderer;
class Factor;

class Camera
{
public:
	Camera(Scene* s);

	void render(Renderer* renderer);
	void render(Renderer* renderer, const std::vector<Factor*>& objs);

	void   setScene(Scene* s);
	Scene* getScene() const;

	void   setDepth(ushort depth);
	ushort getDepth() const;

	void setInputRect(const Rect& rect);
	void setOutputRect(const Rect& rect);

private:
	bool inSight(const Factor& obj) const;

	Scene*    scene;
	ushort    depth;
	Rect      inputRect;
	Rect      outputRect;
};

#endif // CLEM_CAMERA_H_
