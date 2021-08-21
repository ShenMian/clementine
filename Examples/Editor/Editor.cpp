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

        skyboxTexture = Texture2D::create();
        skyboxTexture->loadCubemap(
            {
                "../assets/textures/skybox/right.jpg",
                "../assets/textures/skybox/left.jpg",
                "../assets/textures/skybox/top.jpg",
                "../assets/textures/skybox/bottom.jpg",
                "../assets/textures/skybox/front.jpg",
                "../assets/textures/skybox/back.jpg"
            });

        // 必须是第一个被渲染的物体且关闭深度测试
        auto skybox = Main::registry.create("skybox");
        skybox.add<Material>();
        skybox.add<Mesh>("../assets/models/cube.obj").addTexture(skyboxTexture);

        auto model = Main::registry.create("model");
        model.add<Transform>();
        model.add<Material>();
        // model.add<Mesh>("../assets/models/weapon/m4a1.obj");
        model.add<Mesh>("../../../3DModel/scene/San_Miguel/san-miguel-low-poly.obj");
    }

private:
    std::shared_ptr<Texture2D> skyboxTexture;
};

Application* clem::CreateApplication()
{
    return new App;
}