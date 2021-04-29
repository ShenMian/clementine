// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <vector>

namespace clem
{
class AEntity;
class Archtype;
class Chunk;

class AScene
{
public:
	AEntity createEntity();
	void    destoryEntity(AEntity);
	
private:
	std::vector<Archtype> archtypes;
};

} // namespace clem
