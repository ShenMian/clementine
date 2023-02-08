// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "app/application.hpp"
#include "app/engine.hpp"
#include "app/system/default_system.hpp"

#include "misc/progress_spinner.hpp"

#include <Graphics.h>
#include <fmt/color.h>
#include <fmt/format.h>

#include "audio/device.h"
#include "audio/listener.hpp"
#include "audio/sound.hpp"
#include "audio/source.hpp"

// #include "ecs/array.hpp"

#include "net/linking_context.h"

#include "core/memory_stream.hpp"

namespace fs = std::filesystem;

struct MatricesBuffer
{
	Matrix4 view;
	Matrix4 proj;
	Matrix4 model;
};

class Editor : public Application
{
public:
	Editor() : Application(Config{.window = {.title = "Editor"}}) {}

	void update(float dt) override {}
	void init() override {}
	void deinit() override {}

private:
	Model loadModel(const fs::path& path)
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

	Engine engine;
	engine.addSystem<DefaultSystem>();
	// engine.addSystem<WindowSystem>();
	engine.init(args);

	auto app = new Editor;
	engine.run(*app);
	delete app;
	engine.deinit();

	return 0;
}
