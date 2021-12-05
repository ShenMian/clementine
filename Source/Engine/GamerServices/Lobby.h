// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include <string>

class Lobby
{
public:
	static void queryAsync();

	static void setStringFilter(const std::string& str);
	static void setCountFilter(int count);
};
