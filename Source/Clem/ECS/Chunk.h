// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "config.h"
#include <any>
#include <array>
#include <cassert>
#include <map>
#include <typeindex>
#include <unordered_map>

namespace clem
{

struct alignas(chunk_alignment) Chunk
{
public:
	template <typename Com, typename... Args>
	Com& addComponent(id_type id, Args&&... args);

	template <typename Com>
	void removeComponent(id_type id);

	template <typename Com>
	Com& getComponent(id_type id);

	template <typename Com>
	bool hasComponent(id_type id);

	size_t getSize() const;

	size_t getSizeBytes() const;

	bool empty() const;

private:
	size_t                            size;
	std::array<std::byte, chunk_size> buffer;

	std::unordered_map<id_type, std::unordered_map<TypeIndex, std::any>> components;
};

template <typename Com, typename... Args>
inline Com& Chunk::addComponent(id_type id, Args&&... args)
{
	components[id][Typeid<Com>()] = Com(args...);
	size++;
	return std::any_cast<Com&>(components[id][Typeid<Com>()]);
}

template <typename Com>
inline void Chunk::removeComponent(id_type id)
{
	components[id][Typeid<Com>()].reset();
	size--;
}

template <typename Com>
[[nodiscard]] inline Com& Chunk::getComponent(id_type id)
{
	assert(components[id][Typeid<Com>()].has_value());
	return std::any_cast<Com&>(components[id][Typeid<Com>()]);
}

template <typename Com>
[[nodiscard]] inline bool Chunk::hasComponent(id_type id)
{
	return components[id][Typeid<Com>()].has_value();
}

} // namespace clem
