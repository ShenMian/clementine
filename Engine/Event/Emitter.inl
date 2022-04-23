// Copyright 2021 ShenMian
// License(Apache-2.0)

#include <functional>
#include <typeinfo>
#include <stdexcept>

namespace event
{

template <typename Callback>
struct traits : public traits<decltype(&Callback::operator())>
{
};

template <typename ClassType, typename R, typename... Args>
struct traits<R(ClassType::*)(Args...) const>
{
	typedef std::function<R(Args...)> fn;
};

template <typename Callback>
typename traits<Callback>::fn to_function(Callback& cb)
{
	return static_cast<typename traits<Callback>::fn>(cb);
}

template<typename... Args>
inline void Emitter::emit(const std::string& name, Args... args)
{
	const auto it = listeners.find(name);
	if(it == listeners.end())
		throw std::runtime_error("listener do not exist");
	auto fn = static_cast<std::function<void(Args...)>*>(it->second);
	(*fn)(args...);
}

template<typename Callback>
inline void Emitter::add(const std::string& name, Callback callback)
{
	if(listeners.contains(name))
		throw std::runtime_error("listener already exist");
	auto f = to_function(callback);
	auto fn = new decltype(f)(to_function(callback));
	listeners[name] = static_cast<void*>(fn);
}

inline void Emitter::remove(const std::string& name)
{
	if(!listeners.contains(name))
		return;
	listeners.erase(name);
}

}
