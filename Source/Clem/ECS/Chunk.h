// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AEntity.h"
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
	Com& addComponent(const AEntity&, Args&&... args);

	template <typename Com>
	void removeComponent(const AEntity&);

	template <typename Com>
	Com& getComponent(const AEntity&);

	template <typename Com>
	bool hasComponent(const AEntity&);

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

	std::map<AEntity, std::unordered_map<std::type_index, std::any>> components;
};

template <typename Com, typename... Args>
inline Com& Chunk::addComponent(const AEntity& e, Args&&... args)
{
	components[e][typeid(Com)] = Com(args...);
	size++;
	return std::any_cast<Com&>(components[e][typeid(Com)]);
}

template <typename Com>
inline void Chunk::removeComponent(const AEntity& e)
{
	components[e][typeid(Com)].reset();
	size--;
}

template <typename Com>
[[nodiscard]] inline Com& Chunk::getComponent(const AEntity& e)
{
	return std::any_cast<Com&>(components[e][typeid(Com)]);
}

template <typename Com>
[[nodiscard]] inline bool Chunk::hasComponent(const AEntity& e)
{
	return components[e][typeid(Com)].has_value();
}
} // namespace clem
