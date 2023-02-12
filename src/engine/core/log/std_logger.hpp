// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "logger.hpp"
#include <cstdio>

#pragma once

namespace core
{

/**
 * @brief 标准/错误输出日志记录器.
 */
class StdLogger : public Logger
{
public:
	StdLogger(const std::string& name) : Logger(name) {}

	void info(std::string_view msg) override
	{
		fmt::print("{} {} {} {}\n", fmt::styled("[*]", fmt::fg(fmt::color::blue)), name_,
		           fmt::styled("|", fmt::fg(fmt::color::gray)), msg);
	}

	void good(std::string_view msg) override
	{
		fmt::print("{} {} {} {}\n", fmt::styled("[+]", fmt::fg(fmt::color::green)), name_,
		           fmt::styled("|", fmt::fg(fmt::color::gray)), msg);
	}

	void error(std::string_view msg) override
	{
		fmt::print("{} {} {} {}\n", fmt::styled("[-]", fmt::fg(fmt::color::red)), name_,
		           fmt::styled("|", fmt::fg(fmt::color::gray)), msg);
	}

	void warn(std::string_view msg) override
	{
		fmt::print("{} {} {} {}\n", fmt::styled("[!]", fmt::fg(fmt::color::yellow)), name_,
		           fmt::styled("|", fmt::fg(fmt::color::gray)), msg);
	}

	void flush() override { fflush(stdout); }
};

} // namespace core
