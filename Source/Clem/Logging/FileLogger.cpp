// Copyright 2021 SMS
// License(Apache-2.0)

#include "FileLogger.h"

namespace clem
{

FileLogger::FileLogger(std::string_view name, const std::filesystem::path& path)
    : Logger(name), handle(spdlog::basic_logger_mt(std::string(name), path.string()))
{
}

void FileLogger::info(std::string_view msg)
{
    handle->info(msg);
}

void FileLogger::warn(std::string_view msg)
{
    handle->warn(msg);
}

void FileLogger::error(std::string_view msg)
{
    handle->error(msg);
}

void FileLogger::fatal(const std::string_view msg)
{
    handle->critical(msg);
}

void FileLogger::flush()
{
    handle->flush();
}

void FileLogger::setFormat(const std::string& fmt)
{
    handle->set_pattern(fmt);
}

} // namespace clem