// Copyright 2021 SMS
// License(Apache-2.0)

#include "Chunk.h"

namespace clem
{

size_t Chunk::getSize() const
{
    return size;
}

size_t Chunk::getSizeBytes() const
{
    return buffer.size();
}

bool Chunk::empty() const
{
    return components.empty(); // buffer.empty()
}

} // namespace clem