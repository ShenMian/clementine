// Copyright 2021 SMS
// License(Apache-2.0)
// 摄像机

#ifndef CLEM_CAMERA_H_
#define CLEM_CAMERA_H_

#include <vector>
#include "type.h"

class Scene;
class Sprite;

/// 摄像机
class Camera
{
public:
	Camera();
	explicit Camera(Scene* scene);

	void render(const std::vector<Sprite*>&);

	void   setScene(Scene* scene);
	Scene* getScene() const;

	void setInputPosition(const Point& pos);
	void setOutputPosition(const Point& pos);

	void setSize(Size size);
	Size getSize() const;

	void  setDepth(short depth);
	short getDepth() const;

private:
	Scene* scene;
	Point  inPos, outPos;
	Size   size;
  short  depth;
};

#endif // !CLEM_CAMERA_H_
