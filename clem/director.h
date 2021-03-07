// Copyright 2020 SMS
// License(Apache-2.0)

#ifndef CLEM_DIRECTOR_H_
#define CLEM_DIRECTOR_H_

#include <vector>

class Size;
class Scene;

class Director
{
public:
	static Director* getInstance();

	void run();
	void pause();
	void resume();

	void   pushScene(Scene&);
	void   popScene();
	void   replaceScene(Scene&);
	Scene* getCurrentScene() const;
	
	void  setMsPerUpdate(long ms);
	short getFramesPerSecond() const;

	Size getWinSize() const;

private:
	Director();
	void loop();
	long getCurrentMillSecond() const;

	std::vector<Scene*> scenes;
	bool                paused;
	float               msPerUpdate;
	short               framesPerSecond;

	static Director instance;
};

#endif // !CLEM_DIRECTOR_H_

