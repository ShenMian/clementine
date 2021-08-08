// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Logger.h"
#include <filesystem>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

namespace clem
{

/**
 * @brief 文件日志记录器.
 */
class FileLogger : public Logger
{
    using handle_type = std::shared_ptr<spdlog::logger>;

public:
    FileLogger(std::string_view name, const std::filesystem::path& path);

    void info(std::string_view msg) override;
    void warn(std::string_view msg) override;
    void error(std::string_view msg) override;
    void fatal(const std::string_view msg) override;
    void flush() override;
    void setFormat(const std::string& fmt) override;

private:
    handle_type handle;
};

}; // namespace clem