// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "Clem.h"
#include <map>
#include <string>

int main_(int argc, char* argv[])
{
	clem::Main main;
	return main.main(argc, argv);
}

namespace clem
{

int Main::main(int argc, char * argv[])
{
	parseArgs(argc, argv);

	auto& app = Application();

	app.init();
	app.run();
	app.deinit();

    return 0;
}

void Main::init()
{
	Logger::create("core");
	Logger::create("audio");
	Logger::create("assert");
	Logger::create("networking");
    
	Audio::init();
	Keyboard::init();
}

void Main::deinit()
{
	Keyboard::deinit();
	Audio::deinit();
}

void Main::parseArgs(int argc, char * argv[])
{
	std::map<std::string, std::string> args;

	std::string_view str;
	for(int i = 1; i < argc; i++)
{
		str      = argv[i];
		auto it  = str.find('=');
		auto opt = str.substr(0, it);
		auto val = str.substr(it + 1);
		args.emplace(opt, val);
}

	args.clear();
}

} // namespace clem
