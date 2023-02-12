// Copyright 2023 ShenMian
// License(Apache-2.0)

#include "check.hpp"
#include <functional>
#include <stdexcept>
#include <typeinfo>

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

template <typename... Args>
inline void Emitter::emit(const std::string& event, Args... args)
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

template <typename Callback>
inline void Emitter::on(const std::string& event, Callback callback)
{
	check(listeners.size() >= 10, "warning: too many listeners");

	if(listeners.contains(event))
		throw std::runtime_error("listener already exist");
	auto f           = to_function(callback);
	auto fn          = new decltype(f)(to_function(callback));
	listeners[event] = static_cast<void*>(fn);
}

template <typename Callback>
inline void Emitter::once(const std::string& event, Callback callback)
{
	if(onceListeners.contains(event))
		throw std::runtime_error("listener already exist");
	auto f               = to_function(callback);
	auto fn              = new decltype(f)(to_function(callback));
	onceListeners[event] = static_cast<void*>(fn);
}

inline void Emitter::remove(const std::string& event)
{
	if(!listeners.contains(event))
		return;
	listeners.erase(event);
	onceListeners.erase(event);
}

inline void Emitter::clear()
{
	listeners.clear();
	onceListeners.clear();
}

} // namespace core
