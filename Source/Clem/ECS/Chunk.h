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

struct alignas(chunk_alignment) Chunk
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

	size_t getSize() const;

	size_t getSizeBytes() const;

	bool empty() const;

private:
	size_t                            size;
	std::array<std::byte, chunk_size> buffer;

	std::unordered_map<id_type, std::unordered_map<TypeIndex, std::any>> components;
};

template <typename Com, typename... Args>
inline Com& Chunk::addComponent(const Entity& e, Args&&... args)
{
	components[e.id()][Typeid<Com>()] = Com(args...);
	size++;
	return std::any_cast<Com&>(components[e.id()][Typeid<Com>()]);
}

template <typename Com>
inline void Chunk::removeComponent(const Entity& e)
{
	components[e.id()][Typeid<Com>()].reset();
	size--;
}

template <typename Com>
[[nodiscard]] inline Com& Chunk::getComponent(const Entity& e)
{
	assert(components[e.id()][Typeid<Com>()].has_value());
	return std::any_cast<Com&>(components[e.id()][Typeid<Com>()]);
}

template <typename Com>
[[nodiscard]] inline bool Chunk::hasComponent(const Entity& e)
{
	return components[e.id()][Typeid<Com>()].has_value();
}

} // namespace clem
