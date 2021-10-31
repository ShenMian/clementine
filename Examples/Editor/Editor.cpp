// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem/Clem.h>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std;
using namespace clem;

class CollisionMaterial
{
private:
    Sound sound;
    float friction = 0.f;
};

/**
 * 编辑器.
 */
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

        std::vector<std::future<void>> futures;

#if 0
        {
            auto  entity   = Main::registry.create("m4a1");
            auto& tf       = entity.add<Transform>();
            tf.translation = {0, 0, 0};
            tf.scale       = {0.21, 0.21, 0.21};
            entity.add<Model>("../../../3DModel/weapon/m4a1/m4a1.gltf");
            // entity.add<Model>("../../../3DModel/weapon/m4a1/m4a1.obj");
        }
#endif

#if 1
        {
            auto  entity   = Main::registry.create("crytek_sponza");
            auto& tf       = entity.add<Transform>();
            tf.scale       = {0.1, 0.1, 0.1};
            tf.rotation    = {0, 90, 0};
            tf.translation = {0, -55, -110};
            entity.add<Model>("../../../3DModel/scene/Crytek_Sponza/sponza.obj", true);
        }
#endif

#if 0
        {
            auto entity                   = Main::registry.create("bistro");
            entity.add<Transform>().scale = {0.07, 0.07, 0.07};
            entity.add<Model>("../../../3DModel/scene/Amazon_Lumberyard_Bistro/Exterior/exterior.obj");
            // entity.add<Model>("../../../3DModel/scene/Amazon_Lumberyard_Bistro/Interior/interior.obj");
        }
#endif

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
        auto  skybox = Main::registry.create("skybox");
        auto& model  = skybox.add<Model>("../assets/models/sphere/sphere.obj");
        model.getMaterials().resize(1);
        model.getMaterials()[0].albedo = Texture2D::create("../assets/textures/skybox/sphere.jpg");
        skybox.add<Material>().albedo  = Texture2D::create("../assets/textures/skybox/sphere.jpg");
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
        skybox.add<Transform>();
    }
};

Application* clem::CreateApplication()
{
    return new App;
}