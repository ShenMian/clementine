// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace core
{

/**
 * @brief 事件发射器.
 *
 * 一个用法类似 Node.js EventEmitter 的事件发射器.
 */
class Emitter
{
public:
	/**
	 * @brief 发射事件.
	 *
	 * @param event 事件名称.
	 * @param args  传递给回调函数的参数.
	 */
	template <typename... Args>
	void emit(const std::string& event, Args... args);

	/**
	 * @brief 添加事件回调.
	 *
	 * @param event    事件名称.
	 * @param callback 回调函数.
	 */
	template <typename Callback>
	void on(const std::string& event, Callback callback);

	/**
	 * @brief 添加一次性的事件回调.
	 *
	 * 回调只会在在事件触发后被执行一次.
	 *
	 * @param event    事件名称.
	 * @param callback 回调函数.
	 */
	template <typename Callback>
	void once(const std::string& event, Callback callback);

	/**
	 * @brief 移除事件回调.
	 *
	 * @param event 事件名称.
	 */
	void remove(const std::string& event);

	/**
	 * @brief 移除全部事件回调.
	 */
	void clear();

private:
	std::unordered_map<std::string, void*> listeners;
	std::unordered_map<std::string, void*> onceListeners;
};

} // namespace core

#include "emitter.inl"
