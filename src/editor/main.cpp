// Copyright 2023 ShenMian
// License(Apache-2.0)

#define FMT_HEADER_ONLY

#include "app/application.hpp"
#include "app/engine.hpp"
#include "app/system/default_system.hpp"

#include "misc/progress_spinner.hpp"

#include <Graphics.h>
#include <execution>
#include <filesystem>
#include <fmt/color.h>
#include <fmt/format.h>

#include "audio/device.h"
#include "audio/listener.hpp"
#include "audio/sound.hpp"
#include "audio/source.hpp"

#include "ecs/manager.hpp"
#include "ecs/view.hpp"

#include "core/memory_stream.hpp"
#include "core/thread_pool.hpp"

#include "hid/unix_controller.hpp"

#include "phys/physics_system.hpp"
#include "phys/sphere_collider.hpp"

#include "net/linking_context.h"

namespace fs = std::filesystem;

struct MatricesBuffer
{
	Matrix4 view;
	Matrix4 proj;
	Matrix4 model;
};

struct Tag : public ecs::Component
{
	DECLARE_TYPE

	std::string name;
};

struct Vel : public ecs::Component
{
	DECLARE_TYPE

	float value;
};

struct Acc : public ecs::Component
{
	DECLARE_TYPE

	float value;
};

class Editor : public Application
{
public:
	Editor() : Application(Config{.window = {.title = "Editor"}}) {}

	ecs::Manager             manager;
	std::vector<ecs::Entity> entities;
	core::ThreadPool         thread_pool;
	// std::shared_ptr<hid::Controller> controller = std::make_shared<hid::UnixController>(1);

	void update(core::Time dt) override
	{
		// while(controller->connected())
		// {
		// 	controller->update();
		// 	// controller->vibration(0.05, 0.05);
		// 	if(controller->get(hid::Controller::Button::A))
		// 		std::cout << "A is pressed\n";
		// }
	}

	void init() override {}

	void deinit() override {}

private:
	Model load_model(const fs::path& path)
	{
		ProgressSpinner spinner("Loading model");

		ModelImporter importer;
		auto          model = importer.load(path, [&](float prog) { spinner.setProgress(prog); });
		spinner.markAsComplete();
		fmt::print(fmt::fg(fmt::color::green), "✔ Loading succeeded \n");
		return model;
	}
};

int main(int argc, const char* argv[])
{
	std::vector<std::string_view> args;
	for(int i = 0; i < argc; i++)
		args.emplace_back(argv[i]);

	auto& engine = Engine::get_instance();
	engine.add_system<DefaultSystem>();
	engine.init(args);

	auto app = new Editor;
	engine.run(*app);
	delete app;
	engine.deinit();

	return 0;
}
