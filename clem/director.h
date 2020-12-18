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

	void   pushScene(Scene* s);
	void   popScene();
	Scene* getCurrentScene() const;

	Size getWinSize() const;
	
	void setMsPerUpdate(ushort i);

private:
	Director();
	void loop();

	std::vector<Scene*> scenes;
	std::thread         thread;
	bool                paused;
	long long           updateInterval;
};

#endif // CLEM_DIRECTOR_H_

