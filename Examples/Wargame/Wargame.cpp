// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>
#include <iostream>
#include <string>

using namespace std;
using namespace clem;

class App : public Application
{
public:
	App()
			: Application("Wargame")
	{
	}

	void init() override
	{
		pushScene(scene);
	}

private:
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}
