﻿// Copyright 2021 SMS
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

#if 1
        // 球形天空盒
        auto skyboxTexture = Texture2D::create("../assets/textures/skybox/sphere.jpg");
        auto skybox        = Main::registry.create("skybox");
        skybox.add<Mesh>("../assets/models/sphere/sphere.obj").addTexture(skyboxTexture);
        skybox.add<Material>();
#else
        // 立方体天空盒
        auto skyboxTexture = Texture2D::create();
        skyboxTexture->loadCubemap(
            {"../assets/textures/skybox/cube/right.jpg",
             "../assets/textures/skybox/cube/left.jpg",
             "../assets/textures/skybox/cube/top.jpg",
             "../assets/textures/skybox/cube/bottom.jpg",
             "../assets/textures/skybox/cube/front.jpg",
             "../assets/textures/skybox/cube/back.jpg"});
        auto skybox = Main::registry.create("skybox");
        skybox.add<Mesh>("../assets/models/cube.obj").addTexture(skyboxTexture);
        skybox.add<Material>();
#endif

        auto model = Main::registry.create("model");
        model.add<Transform>();
        model.add<Material>();
        model.add<Mesh>("../assets/models/weapon/m4a1.obj");
        // model.add<Mesh>("../../../3DModel/scene/Amazon_Lumberyard_Bistro/Exterior/exterior.obj");
        // model.add<Mesh>("../../../3DModel/scene/San_Miguel/san-miguel-low-poly.obj");
    }
};

Application* clem::CreateApplication()
{
    return new App;
}