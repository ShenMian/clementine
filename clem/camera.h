// Copyright 2020 SMS
// License(Apache-2.0)
// 场景摄像机

#ifndef CLEM_CAMERA_H_
#define CLEM_CAMERA_H_

#include <vector>
#include "type.h"
#include "renderer.h"

typedef unsigned short ushort;

class Scene;
class Renderer;
class Factor;

class Camera
{
public:
<<<<<<< HEAD
	Camera(Scene* s);
=======
	Camera();
	Camera(Scene* scene);

	void render();
>>>>>>> bb08b426e997f6b9a83dcf3eed3b18de28ed7221

	void setScene(Scene* scene);

<<<<<<< HEAD
	void   setScene(Scene* s);
	Scene* getScene() const;
=======
	void setInputPosition(const Point& pos);
	void setOutputPosition(const Point& pos);
>>>>>>> bb08b426e997f6b9a83dcf3eed3b18de28ed7221

	void setSize(Size size);
	Size getSize() const;
	
	void   setDepth(ushort depth);
	ushort getDepth() const;

private:
<<<<<<< HEAD
	bool inSight(const Factor& obj) const;

	Scene*    scene;
	ushort    depth;
	Rect      inputRect;
	Rect      outputRect;
=======
	Scene* scene;
	Point  inPos, outPos;
	Size   size;
  ushort depth;
	static Renderer renderer;
>>>>>>> bb08b426e997f6b9a83dcf3eed3b18de28ed7221
};

#endif // CLEM_CAMERA_H_
