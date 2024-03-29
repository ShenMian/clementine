// Copyright 2022 SMS
// License(Apache-2.0)

#pragma once

#include "core/logger/file_logger.hpp"
#include "core/logger/std_logger.hpp"

#include "core/emitter.hpp"
#include "core/timer.hpp"

#include "app/application.hpp"
#include "app/system/system.hpp"

#include <Graphics.h>
#include <chrono>
#include <concepts>
#include <csignal>
#include <fmt/format.h>
#include <memory>
#include <numeric>
#include <ranges>
#include <ratio>
#include <thread>

class Engine
{
public:
	static Engine& get_instance()
	{
		static Engine engine;
		return engine;
	}

	void run(Application& app)
	{
		app.init();

		core::Timer<std::chrono::steady_clock> timer;
		while(!request_exit_)
		{
			const auto dt = timer.get_time();
			timer.restart();

			app.update(dt);

			const core::Time min_dt = core::Time::microseconds(std::round(1000000 / max_frame_rate_));
			while(timer.get_time() < min_dt)
				std::this_thread::sleep_for(std::chrono::microseconds(1));

			update_average_fps();
		}

		app.deinit();
	}

	template <std::derived_from<System> T>
	void add_system()
	{
		CLEM_DEBUG_CHECK(!has_system<T>());
		systems_.push_back(std::make_shared<T>());
	}

	template <std::derived_from<System> T>
	bool has_system() const
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

		parse_args(args);

		Renderer::setAPI(Renderer::API::OpenGL);

		for(size_t i = 0; i < systems_.size(); i++)
		{
			core::Timer<> timer;
			systems_[i]->init(*this);
			CLEM_LOG_INFO("engine", fmt::format("system '{}' init completed ({} ms)'", systems_[i]->id(),
			                                    timer.get_time().get_milliseconds()));
		}

		std::signal(SIGINT, handle_signal);
	}

	void deinit()
	{
		window_ = nullptr;

		// for(auto& sys : systems_ | std::views::reverse)
		for(ptrdiff_t i = systems_.size() - 1; i >= 0; i--)
		{
			auto& sys = systems_[i];
			CLEM_LOG_INFO("engine", fmt::format("deinit system '{}'", sys->id()));
			sys->deinit(*this);
			CLEM_DEBUG_CHECK(sys.use_count() == 1);
		}

		delete core::Logger::get("engine");
	}

	std::shared_ptr<Window> window() { return window_; }
	void                    window(std::shared_ptr<Window> win) { window_ = win; }

	core::Emitter& emitter() { return emitter_; }

	/**
	 * @brief 获取平均帧速率.
	 *
	 * @return float 平均帧速率.
	 */
	float average_frame_rate() const noexcept { return avg_fps_; }

	/**
	 * @brief 请求退出.
	 */
	void request_exit() { request_exit_ = true; }

private:
	Engine() = default;

	void parse_args(const std::vector<std::string_view>& args)
	{
		/*for(auto arg : args)
		{
		    if(arg.starts_with("--render_api="))
		        fmt::print("Render API: {}\n", arg.substr(arg.find_first_of("=") + 1));
		}*/
	}

	void update_average_fps()
	{
		frames_counter++;
		if(frame_rate_counter_timer.get_time() >= avg_fps_update_interval_)
		{
			frame_rate_counter_timer.restart();
			const float factor = 0.9f;
			avg_fps_ = factor * avg_fps_ + (1.0 - factor) * (frames_counter / avg_fps_update_interval_.get_seconds());
			frames_counter = 0;
		}
	}

	static void handle_signal(int signal)
	{
		auto to_string = [](int signal) -> std::optional<std::string_view> {
			switch(signal)
			{
			case SIGABRT:
				return "SIGABRT";

			case SIGFPE:
				return "SIGFPE";

			case SIGILL:
				return "SIGILL";

			case SIGINT:
				return "SIGINT";

			case SIGSEGV:
				return "SIGSEGV";

			case SIGTERM:
				return "SIGTERM";
			}
			return std::nullopt;
		};
		CLEM_LOG_WARN("engine", fmt::format("signal received: '{}'", to_string(signal).value()));
		Engine::get_instance().request_exit();
	}

	core::Emitter                        emitter_;
	std::vector<std::shared_ptr<System>> systems_;
	std::shared_ptr<Window>              window_;

	bool  request_exit_   = false;
	float max_frame_rate_ = 144.f;

	core::Time                             avg_fps_update_interval_ = core::Time::seconds(1);
	float                                  avg_fps_                 = max_frame_rate_;
	size_t                                 frames_counter           = 0;
	core::Timer<std::chrono::steady_clock> frame_rate_counter_timer;
};
