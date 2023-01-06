// Copyright 2022 SMS
// License(Apache-2.0)

#pragma once

#include <fmt/color.h>
#include <fmt/format.h>
#include <string>
#include <thread>
#include <vector>

class ProgressSpinner
{
public:
	ProgressSpinner(const std::string& text) : text_(text)
	{
		thread_ = std::jthread([&](std::stop_token stoken) {
			while(true)
			{
				print();
				for(int i = 0; i < 25; i++)
				{
					if(stoken.stop_requested())
						return;
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
		});
		thread_.detach();
	}

	virtual ~ProgressSpinner() noexcept { markAsComplete(); }

	void markAsComplete() noexcept
	{
		if(isComplete())
			return;
		thread_.request_stop();
	}

	void print()
	{
		fmt::print(fmt::fg(fmt::color::yellow), "{} {}% {}  \r", states[frame_++ % states.size()],
		           (int)std::round(progress_ * 100), text_);
	}

	bool isComplete() noexcept { return thread_.get_stop_token().stop_requested(); }
	void setProgress(float prog) noexcept { progress_ = prog; }

private:
	std::string              text_;
	std::vector<std::string> states    = {"⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁"};
	unsigned int             frame_    = 0;
	float                    progress_ = 0.f;
	std::jthread             thread_;
};
