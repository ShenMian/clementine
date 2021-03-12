// Copyright 2020 SMS
// License(Apache-2.0)
// 导演

#ifndef CLEM_DIRECTOR_H_
#define CLEM_DIRECTOR_H_

#include <vector>

class Size;
class Scene;

/// 导演, 管理主循环和场景
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
	void  setMsPerRender(long ms);
	short getFramesPerSecond() const;

	Size getWinSize() const;

private:
	Director();
	void loop();
	void update(long dt);
	void render(long dt);
	long getCurrentMillSecond() const;

	std::vector<Scene*> scenes;
	bool                paused;
	long                msPerUpdate;
	long                msPerRender;
	short               framesPerSecond;

	static Director instance;
};

#endif // !CLEM_DIRECTOR_H_

