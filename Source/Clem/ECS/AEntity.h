// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>

namespace clem
{
class AScene;

class AEntity
{
public:
	AEntity(size_t id, AScene& scene);

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

	bool operator==(const AEntity& rhs) const;
	bool operator<(const AEntity& rhs) const;

private:
	size_t  id;
	AScene& scene;
};

template <typename Com>
bool AEntity::hasComponent() const
{
	return false;
}

template <typename Com, typename T, typename... Types>
bool AEntity::hasComponent() const
{
	return hasComponent<Com>() && hasComponent<T, Types...>();
}
} // namespace clem
