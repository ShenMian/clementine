// Copyright 2021 SMS
// License(Apache-2.0)

#include "AScene.h"
#include "Archtype.h"
#include <algorithm>

namespace clem
{

struct EntityInfo
{
	Archtype                                   archtype;
	std::unordered_map<std::type_index, void*> components;
};

void AScene::view(const Archtype& archtype)
{
	auto it = std::find(archtypes.begin(), archtypes.end(), archtype);
	
}

class Iterator
{
	Iterator& operator++();
	Iterator& operator++(int);
};

} // namespace clem
