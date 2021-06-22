// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Entity.h"
#include "config.h"
#include <any>
#include <array>
#include <map>
#include <typeindex>
#include <unordered_map>

namespace clem
{
struct alignas(chunkAlignment) Chunk
{
public:
	template <typename Com, typename... Args>
	Com& addComponent(const Entity&, Args&&... args);

	template <typename Com>
	void removeComponent(const Entity&);

	template <typename Com>
	Com& getComponent(const Entity&);

	template <typename Com>
	bool hasComponent(const Entity&);

	size_t getSize() const
	{
		return size;
	}

	size_t getSizeBytes() const
	{
		return buffer.size();
	}

	constexpr size_t getMaxSize() const
	{
		return 0;
	}

private:
	size_t                           size;
	std::array<std::byte, chunkSize> buffer;

	std::map<Entity, std::unordered_map<TypeIndex, std::any>> components;
};

template <typename Com, typename... Args>
inline Com& Chunk::addComponent(const Entity& e, Args&&... args)
{
	components[e][Typeid<Com>()] = Com(args...);
	size++;
	return std::any_cast<Com&>(components[e][Typeid<Com>()]);
}

template <typename Com>
inline void Chunk::removeComponent(const Entity& e)
{
	components[e][Typeid<Com>()].reset();
	size--;
}

template <typename Com>
[[nodiscard]] inline Com& Chunk::getComponent(const Entity& e)
{
	return std::any_cast<Com&>(components[e][Typeid<Com>()]);
}

template <typename Com>
[[nodiscard]] inline bool Chunk::hasComponent(const Entity& e)
{
	return components[e][Typeid<Com>()].has_value();
}
} // namespace clem
