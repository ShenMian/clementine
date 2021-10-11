// Copyright 2021 SMS
// License(Apache-2.0)

#include "MemoryStream.h"

void MemoryStream::writeBytes(const void* data, size_t size)
{
    writeBits(data, size * 8);
}

void MemoryStream::writeBits(const void* data, size_t size)
{
    if(bitSize + size > buf.size() * 8)
        buf.resize(buf.size() * 2);

    auto ptr = static_cast<const std::byte*>(data);
    while(size >= 8)
    {
        writeBits(*ptr++, 8);
        size -= 8;
    }
    if(size)
        writeBits(*ptr, size);

    bitSize += size;
}

void MemoryStream::serialize(const void* data, const Properties& properties)
{
    for(const auto& member : properties.getMembers())
    {
        const auto ptr = (uint64_t*)data + member.offset;
        if(member.type == typeid(int8_t))
            write(*(const int8_t*)ptr);
        else if(member.type == typeid(int16_t))
            write(*(const int16_t*)ptr);
        else if(member.type == typeid(int32_t))
            write(*(const int32_t*)ptr);
        else if(member.type == typeid(int64_t))
            write(*(const int64_t*)ptr);
        else if(member.type == typeid(uint8_t))
            write(*(const uint8_t*)ptr);
        else if(member.type == typeid(uint16_t))
            write(*(const uint16_t*)ptr);
        else if(member.type == typeid(uint32_t))
            write(*(const uint32_t*)ptr);
        else if(member.type == typeid(uint64_t))
            write(*(const uint64_t*)ptr);
        else if(member.type == typeid(float))
            write(*(const float*)ptr);
        else if(member.type == typeid(double))
            write(*(const double*)ptr);
        else
            assert(false);
    }
}

void MemoryStream::readBytes(void* data, size_t size)
{
    readBits(data, size * 8);
}

void MemoryStream::readBits(void* data, size_t size)
{
}

void MemoryStream::unserialize(void* data, const Properties& properties)
{
    for(const auto& member : properties.getMembers())
    {
        const auto ptr = (uint64_t*)data + member.offset;
        if(member.type == typeid(int8_t))
            read(*(int8_t*)ptr);
        else if(member.type == typeid(int16_t))
            read(*(int16_t*)ptr);
        else if(member.type == typeid(int32_t))
            read(*(int32_t*)ptr);
        else if(member.type == typeid(int64_t))
            read(*(int64_t*)ptr);
        else if(member.type == typeid(uint8_t))
            read(*(uint8_t*)ptr);
        else if(member.type == typeid(uint16_t))
            read(*(uint16_t*)ptr);
        else if(member.type == typeid(uint32_t))
            read(*(uint32_t*)ptr);
        else if(member.type == typeid(uint64_t))
            read(*(uint64_t*)ptr);
        else if(member.type == typeid(float))
            read(*(float*)ptr);
        else if(member.type == typeid(float))
            read(*(float*)ptr);
        else if(member.type == typeid(double))
            read(*(double*)ptr);
        else
            assert(false);
    }
}

size_t MemoryStream::getByteSize() const
{
    return (bitSize + 7) / 8;
}

size_t MemoryStream::getBitSize() const
{
    return bitSize;
}

void MemoryStream::writeBits(std::byte data, size_t size)
{
    const auto byteOffset = getByteSize();
    const auto bitOffset  = getBitSize() & 0x7; // 获取最后 3 bits, 7h = 111b, 2^3 = 8

    buf[byteOffset] |= data << bitOffset;
}
