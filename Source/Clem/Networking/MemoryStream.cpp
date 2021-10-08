// Copyright 2021 SMS
// License(Apache-2.0)

#include "MemoryStream.h"

void MemoryStream::writeBytes(const void* data, size_t size)
{
    writeBits(data, size * 8);
}

void MemoryStream::writeBits(const void* data, size_t size)
{
}

void MemoryStream::readBytes(void* data, size_t size)
{
    readBits(data, size * 8);
}

void MemoryStream::readBits(void* data, size_t size)
{
}

size_t MemoryStream::byteSize() const
{
    return (size + 7) / 8;
}

size_t MemoryStream::bitSize() const
{
    return size;
}
