// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_DIRECTOR_H_
#define CLEM_DIRECTOR_H_

#include <vector>
#include <thread>

typedef unsigned short ushort;
class Scene;

class Director
{
public:
	static Director& instance();

	void run();

	void setPerFrameInterval(ushort i);

	void pushScene(Scene* s);
	void popScene();

private:
	Director();
	void loop();

	ushort              perFrameInterval;
	std::vector<Scene*> scenes;
	std::thread         thread;
};

#endif // CLEM_DIRECTOR_H_

