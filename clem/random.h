// Copyright 2020 SMS
// License(Apache-2.0)
// ³¡¾°

#ifndef CLEM_RANDOM_H_
#define CLEM_RANDOM_H_

#include <random>

class Random
{
public:
	void seed();

private:
	std::mt19937 generator;
};

#endif // !CLEM_RANDOM_H_
