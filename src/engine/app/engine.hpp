// Copyright 2022 SMS
// License(Apache-2.0)

#pragma once

#include "core/log/file_logger.hpp"
#include "core/log/std_logger.hpp"

#include "core/emitter.hpp"
#include "core/timer.hpp"

#include "app/application.hpp"
#include "app/system/system.hpp"

#include <Graphics.h>
#include <concepts>
#include <fmt/format.h>
#include <memory>
#include <ranges>

class Engine
{
public:
	void run(Application& app)
	{
		core::Timer timer;
		const auto  dt = timer.get_time();

		app.init();

		bool requestExit = false;

		while(!requestExit)
		{
			const auto dt = timer.get_time();
			timer.restart();

			app.update(dt);

			// TODO: debug
			// requestExit = true;
		}

		app.deinit();
	}

	template <std::derived_from<System> T>
	void addSystem()
	{
		check(!hasSystem<T>());
		systems_.push_back(std::make_shared<T>());
	}

	template <std::derived_from<System> T>
	bool hasSystem() const
	{
		return std::ranges::find_if(systems_, [](const auto& sys) { return sys->id() == T().id(); }) != systems_.end();
	}

	void init(const std::vector<std::string_view>& args)
	{
#if TARGET_OS == OS_WIN
		SetConsoleOutputCP(CP_UTF8); // 启用 UTF-8 支持
#endif

		new core::StdLogger("engine");
		CLEM_LOG_INFO("engine", "engine init begin");

		parseArgs(args);

		Renderer::setAPI(Renderer::API::OpenGL);

		for(size_t i = 0; i < systems_.size(); i++)
		{
			core::Timer timer;
			systems_[i]->init(*this);
			CLEM_LOG_INFO("engine", fmt::format("system '{}' init completed ({} ms)'", systems_[i]->id(),
			                                    timer.get_time().get_milliseconds()));
		}
	}

	void deinit()
	{
		window_ = nullptr;

		// for(auto& sys : systems_ | std::views::reverse)
		for(ssize_t i = systems_.size() - 1; i >= 0; i--)
		{
			auto& sys = systems_[i];
			CLEM_LOG_INFO("engine", fmt::format("deinit system '{}'", sys->id()));
			sys->deinit(*this);
			check(sys.use_count() == 1);
		}

		delete core::Logger::get("engine");
	}

	std::shared_ptr<Window> window() const { return window_; }

	void window(std::shared_ptr<Window> win) { window_ = win; }

private:
	void parseArgs(const std::vector<std::string_view>& args)
	{
		/*for(auto arg : args)
		{
		    if(arg.starts_with("--render_api="))
		        fmt::print("Render API: {}\n", arg.substr(arg.find_first_of("=") + 1));
		}*/
	}

	std::vector<std::shared_ptr<System>> systems_;
	std::shared_ptr<Window>              window_;
	core::Emitter                        emitter_;
};
