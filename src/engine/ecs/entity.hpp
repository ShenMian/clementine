// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstdint>

namespace ecs
{

class Registry;

/**
 * @brief 实体.
 */
class Entity
{
public:
	using id_type      = uint32_t;
	using version_type = uint32_t;

	Entity() = default;
	Entity(id_type id, version_type ver, Registry& reg) : id_(id), version_(ver), registry(reg) {}

	auto id() const noexcept { return id_; }
	auto version() const noexcept { return version_; }

	bool operator==(const Entity& rhs) const
	{
		return id_ == rhs.id_ && version_ == rhs.version_ && &registry == &rhs.registry;
	};

private:
	id_type      id_;
	version_type version_;
	Registry&    registry;

	friend class Registry;
};

} // namespace ecs
