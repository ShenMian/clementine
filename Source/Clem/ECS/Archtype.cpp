// Copyright 2021 SMS
// License(Apache-2.0)

#include "Archtype.h"
#include <algorithm>

namespace clem
{

Archtype::Archtype(std::unordered_set<TypeIndex>&& types)
    : types(std::move(types))
{
}

void Archtype::clear()
{
    types.clear();
}

[[nodiscard]] size_t Archtype::hashCode() const
{
    size_t code = 0;
    for(auto type : types)
        code ^= type.hash_code();
    return code;
}

} // namespace clem