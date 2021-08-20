// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem/Clem.h>
#include <future>
#include <iostream>
#include <string>

using namespace std;
using namespace clem;

class App : public Application
{
public:
    App()
        : Application("Clementine")
    {
    }

    void init() override
    {
        Main::getWindow()->add(new ui::Dockspace);
        Main::getWindow()->add(new ui::Viewport);
        Main::getWindow()->add(new ui::Setting);
        Main::getWindow()->add(new ui::Browser);
        Main::getWindow()->add(new ui::Hierarchy);
        Main::getWindow()->add(new ui::Properties);

        Main::getWindow()->setIcon("../assets/textures/icons/game_controller.png");

        // cube.obj, cone.obj, sphere.obj, teapot.obj, statue.obj, wood_dining_chair
        auto model = Main::registry.create("model");
        model.add<Transform>();
        model.add<Model>("../assets/models/cube.obj");
        model.add<Material>();
    }

private:
};

Application* clem::CreateApplication()
{
    return new App;
}