// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_DIRECTOR_H_
#define CLEM_DIRECTOR_H_

#include <vector>

typedef unsigned short ushort;
class Scene;

class Director
{
public:
	Director& instance();

	void setPerFrameInterval(ushort i);

	void pushScene(Scene* s);
	void popScene(Scene* s);

private:
	Director();
	void mainLoop();

	ushort              perFrameInterval;
	std::vector<Scene*> scenes;
};

#endif // CLEM_DIRECTOR_H_

