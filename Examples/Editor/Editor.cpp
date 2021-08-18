// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem/Clem.h>
#include <future>
#include <iostream>
#include <string>
#include "Clem/Rendering/OpenGL/GLFrameBuffer.h"

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
        // Main::getWindow()->add(new ui::Dockspace);
        Main::getWindow()->add(new ui::Setting);
        Main::getWindow()->add(new ui::Browser);
        Main::getWindow()->add(new ui::Hierarchy);
        Main::getWindow()->add(new ui::Properties);

        auto model = Main::registry.create("model");
        model.add<Transform>();
        model.add<Model>();
        
        FrameBuffer::map.insert({"scene", FrameBuffer::create({1920 * 0.7, 1080 * 0.7}, 1)});
    }

private:
    std::shared_ptr<FrameBuffer> framebuffer = FrameBuffer::create({1920 * 0.7, 1080 * 0.7}, 1);
};

Application* clem::CreateApplication()
{
    return new App;
}