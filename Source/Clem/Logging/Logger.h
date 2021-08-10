// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <format>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace clem
{

constexpr int log_level_info  = 0;
constexpr int log_level_warn  = 1;
constexpr int log_level_error = 2;
constexpr int log_level_fatal = 3;

constexpr int log_active_level = log_level_info; /// 要记录的最低日志等级

static_assert(log_level_info <= log_active_level && log_active_level <= log_level_fatal);

/**
 * @brief 日志记录器.
 */
class Logger
{
public:
    Logger(std::string_view name);

    /**
	* @brief 信息.
	*
	* @param msg 消息.
	*/
    virtual void info(std::string_view msg) = 0;

    /**
	* @brief 警告.
	*
	* @param msg 消息.
	*/
    virtual void warn(std::string_view msg) = 0;

    /**
	* @brief 错误.
	*
	* @param msg 消息.
	*/
    virtual void error(std::string_view msg) = 0;

    /**
	* @brief 致命错误.
	*
	* @param msg 消息.
	*/
    virtual void fatal(const std::string_view msg) = 0;

    /**
	* @brief 将缓存中的记录输出到指定位置.
	*/
    virtual void flush() = 0;

    /**
	* @brief 设置记录格式.
	*
	* @param fmt 格式控制字符串.
	*/
    virtual void setFormat(const std::string& fmt) = 0;

    /**
	* @brief 获取日志记录器名称.
	*/
    const std::string& getName() const;

    static void                    add(std::shared_ptr<Logger> logger);
    static void                    remove(const std::string& name);
    static std::shared_ptr<Logger> get(const std::string& name);

    static void flushAll();

    static void init();
    static void deinit();

private:
    std::string name;

    static std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
};

}; // namespace clem

#define CLEM_LOG_INFO(name, msg)  ::clem::Logger::get(name)->info(msg)
#define CLEM_LOG_WARN(name, msg)  ::clem::Logger::get(name)->warn(msg)
#define CLEM_LOG_ERROR(name, msg) ::clem::Logger::get(name)->error(msg)
#define CLEM_LOG_FATAL(name, msg) ::clem::Logger::get(name)->fatal(msg)
#define CLEM_LOG_FLUSH()          ::clem::Logger::flushAll()