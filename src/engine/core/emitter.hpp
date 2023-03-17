// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "core/check.hpp"
#include <functional>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>

namespace core
{

template <typename Callback>
struct traits : public traits<decltype(&Callback::operator())>
{
};

template <typename ClassType, typename R, typename... Args>
struct traits<R (ClassType::*)(Args...) const>
{
	typedef std::function<R(Args...)> fn;
};

template <typename Callback>
typename traits<Callback>::fn to_function(Callback& cb)
{
	return static_cast<typename traits<Callback>::fn>(cb);
}

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
	void emit(const std::string& event, Args... args)
	{
		{
			const auto it = listeners.find(event);
			if(it != listeners.end())
			{
				auto fn = static_cast<std::function<void(Args...)>*>(it->second);
				(*fn)(args...);
			}
		}
		{
			const auto it = onceListeners.find(event);
			if(it != onceListeners.end())
			{
				auto fn = static_cast<std::function<void(Args...)>*>(it->second);
				(*fn)(args...);
				onceListeners.erase(event);
			}
		}
	}

	/**
	 * @brief 添加事件回调.
	 *
	 * @param event    事件名称.
	 * @param callback 回调函数.
	 */
	template <typename Callback>
	void on(const std::string& event, Callback callback)
	{
		CLEM_DEBUG_CHECK(listeners.size() >= 10, "warning: too many listeners");

		if(listeners.contains(event))
			throw std::runtime_error("listener already exist");
		auto f           = to_function(callback);
		auto fn          = new decltype(f)(to_function(callback));
		listeners[event] = static_cast<void*>(fn);
	}

	/**
	 * @brief 添加一次性的事件回调.
	 *
	 * 回调只会在在事件触发后被执行一次.
	 *
	 * @param event    事件名称.
	 * @param callback 回调函数.
	 */
	template <typename Callback>
	void once(const std::string& event, Callback callback)
	{
		if(onceListeners.contains(event))
			throw std::runtime_error("listener already exist");
		auto f               = to_function(callback);
		auto fn              = new decltype(f)(to_function(callback));
		onceListeners[event] = static_cast<void*>(fn);
	}

	/**
	 * @brief 移除事件回调.
	 *
	 * @param event 事件名称.
	 */
	void remove(const std::string& event)
	{
		if(!listeners.contains(event))
			return;
		listeners.erase(event);
		onceListeners.erase(event);
	}

	/**
	 * @brief 移除全部事件回调.
	 */
	void clear()
	{
		listeners.clear();
		onceListeners.clear();
	}

private:
	std::unordered_map<std::string, void*> listeners;
	std::unordered_map<std::string, void*> onceListeners;
};

} // namespace core
