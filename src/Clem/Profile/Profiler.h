// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <vector>

class Session;

class Profiler
{
public:
	static Profiler& get();

	void addSession(Session& s);

private:
	std::vector<Session> sessions;
};
