// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"

using namespace std;

class Chess : public Application
{
public:
	Chess()
			: Application("Chess"), scene(make_shared<Scene>())
	{
		pushScene(scene);

		auto  canvas = scene->createEntity("canvas");
		auto& text   = canvas.addComponent<Text>();
		text.text    = L"Hello World!";
	}

private:
	std::shared_ptr<Scene> scene;
};
