// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <string>
#include <unordered_map>

namespace event
{

/**
 * @brief 事件发射器.
 */
class Emitter
{
public:
	/**
	 * @brief 发射事件.
	 *
	 * @param name 事件名称.
	 * @param args 传递给回调函数的参数.
	 */
	template <typename... Args>
	void emit(const std::string& name, Args... args);

	/**
	 * @brief 添加事件回调.
	 *
	 * @param name     事件名称.
	 * @param callback 回调函数.
	 */
	template <typename Callback>
	void add(const std::string& name, Callback callback);

	/**
	 * @brief 移除事件回调.
	 *
	 * @param name 事件名称.
	 */
	void remove(const std::string& name);

private:
	std::unordered_map<std::string, void*> listeners;
};

}

#include "Emitter.inl"
