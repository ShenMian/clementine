// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_DIRECTOR_H_
#define CLEM_DIRECTOR_H_

#include <vector>
#include <thread>

typedef unsigned short ushort;

class Size;
class Scene;
class Renderer;

class Director
{
public:
	static Director* getInstance();

	void run();
	void pause();
	void resume();
	void reset();

	void   pushScene(Scene* scene);
	void   popScene();
	void   replaceScene(Scene* scene);
	Scene* getCurrentScene() const;
	
	void setMsPerUpdate(ushort i);

	Size getWinSize() const;

private:
	Director();
	void loop();

	std::vector<Scene*> scenes;
	bool                paused;
	long                msPerUpdate;
};

#endif // CLEM_DIRECTOR_H_

