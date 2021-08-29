// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem/Clem.h>
#include <future>
#include <iostream>
#include <string>
#include <thread>

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
        Main::getWindow()->setIcon("../assets/textures/icons/game_controller.png");

        createPanels();
        createSkybox();

        auto model                      = Main::registry.create("model");
        model.add<Transform>().rotation = {0, 90, 0};

        // model.add<Model>("../assets/models/scene.obj", true);
        model.add<Model>("../../../3DModel/weapon/m4a1/m4a1.obj", true);
        model.get<Transform>().translation = {0, 0, -20};

        // model.add<Model>("../../../3DModel/scene/Crytek_Sponza/sponza.obj", true);
        // model.get<Transform>().scale = {0.1, 0.1, 0.1};

        // model.add<Model>("../../../3DModel/scene/Amazon_Lumberyard_Bistro/Exterior/exterior.obj");
        // model.add<Model>("../../../3DModel/scene/Amazon_Lumberyard_Bistro/Interior/interior.obj");

        // model.add<Model>("../../../3DModel/scene/San_Miguel/san-miguel-low-poly.obj", true);
    }

private:
    void createPanels()
    {
        Main::getWindow()->add(new ui::Dockspace);
        Main::getWindow()->add(new ui::Viewport);
        Main::getWindow()->add(new ui::Setting);
        Main::getWindow()->add(new ui::Browser);
        Main::getWindow()->add(new ui::Hierarchy);
        Main::getWindow()->add(new ui::Properties);
    }

    void createSkybox()
    {
#if 1
        // 球形天空盒
        auto skybox = Main::registry.create("skybox");
        auto& model = skybox.add<Model>("../assets/models/sphere/sphere.obj");
        model.getMaterials().resize(1);
        model.getMaterials()[0].tex.diffuse = Texture2D::create("../assets/textures/skybox/sphere.jpg");
        skybox.add<Material>().tex.diffuse = Texture2D::create("../assets/textures/skybox/sphere.jpg");
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
        skybox.add<Model>("../assets/models/cube.obj");
        skybox.add<Material>().albedo = skyboxTexture;
#endif
    }
};

Application* clem::CreateApplication()
{
    return new App;
}