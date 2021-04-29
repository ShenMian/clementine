// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

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

	bool isValid() const;

private:
	size_t id;
};

} // namespace clem
