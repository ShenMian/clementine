// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstdint>

namespace ecs
{

class Manager;

/**
 * @brief 实体.
 */
class Entity
{
public:
	using id_type      = uint32_t;
	using version_type = uint32_t;

	Entity()              = default;
	Entity(const Entity&) = default;
	Entity(id_type id, version_type version) : id_(id), version_(version) {}

	auto id() const noexcept { return id_; }
	auto version() const noexcept { return version_; }

	bool operator==(const Entity& rhs) const noexcept { return id_ == rhs.id_ && version_ == rhs.version_; }

private:
	id_type      id_;
	version_type version_;

	friend class Manager;
};

} // namespace ecs
