// Copyright 2023 ShenMian
// License(Apache-2.0)

#include <string>

#pragma once

class Engine;

class System
{
public:
	const std::string& id() const noexcept { return id_; }

	virtual void init(Engine& engine)   = 0;
	virtual void deinit(Engine& engine) = 0;

protected:
	System(const std::string& id) : id_(id) {}

private:
	std::string id_;
};
