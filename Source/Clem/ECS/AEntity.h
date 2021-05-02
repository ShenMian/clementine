// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>

namespace clem
{

class AEntity
{
public:
	template <typename Com, typename... Args>
	Com& addComponent(Args&&... args);

	template <typename Com>
	void removeComponent();

	template <typename Com>
	Com& getComponent() const;

	template <typename Com>
	bool hasComponent() const;

	template <typename T, typename V, typename... Types>
	bool hasComponent() const;

	bool isValid() const;

private:
	size_t id;
};

template <typename T, typename V, typename... Types>
bool AEntity::hasComponent() const
{
	return hasComponent<T>() && hasComponent<V, Types...>();
}

} // namespace clem
