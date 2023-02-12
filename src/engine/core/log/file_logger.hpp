// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "logger.hpp"
#include <filesystem>
#include <fstream>

#pragma once

namespace core
{

/**
 * @brief 文件日志记录器.
 */
class FileLogger : public Logger
{
public:
	FileLogger(const std::string& name, const std::filesystem::path& path) : Logger(name), path_(path)
	{
		file_.open(path);
		if(!file_.is_open())
			throw std::runtime_error("can not open file");
	}

	virtual ~FileLogger() { file_.close(); }

	void info(std::string_view msg) override
	{
		// TODO
		// file_ << std::chrono::system_clock::now() << name_ << " [INFO] " << msg << '\n';
	}

	void good(std::string_view msg) override
	{
		// TODO
		// file_ << std::chrono::system_clock::now() << name_ << " [GOOD] " << msg << '\n';
	}

	void error(std::string_view msg) override
	{
		// TODO
		// file_ << std::chrono::system_clock::now() << name_ << " [ERR ] " << msg << '\n';
	}

	void warn(std::string_view msg) override
	{
		// TODO
		// file_ << std::chrono::system_clock::now() << name_ << " [WARN] " << msg << '\n';
	}

	void flush() override { file_.flush(); }

private:
	std::filesystem::path path_;
	std::ofstream         file_;
};

} // namespace core
