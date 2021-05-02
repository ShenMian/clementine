// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <set>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace clem
{
class Chunk;

class Archtype
{
	using type_set = std::set<std::type_index>;

public:
	Archtype(const type_set&);

	bool all(const Archtype&) const;
	bool any(const Archtype&) const;
	bool none(const Archtype&) const;

	bool operator==(const Archtype& rhs) const;
	bool operator<(const Archtype& rhs) const;

private:
	type_set types;
};

} // namespace clem
