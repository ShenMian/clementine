// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Properties.hpp"
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <vector>

class MemoryStream
{
public:
    template <typename T>
    void write(T data);

    void writeBytes(const void* data, size_t size);

    void writeBits(const void* data, size_t size);

    void serialize(const void* data, const Properties& properties);

    template <typename T>
    void read(T& data);

    void readBytes(void* data, size_t size);

    void readBits(void* data, size_t size);

    void unserialize(void* data, const Properties& properties);

    size_t byteSize() const;
    size_t bitSize() const;

    template <typename T>
    MemoryStream& operator<<(T);

    template <typename T>
    MemoryStream& operator>>(T&);

private:
    size_t                 size = 0;
    std::vector<std::byte> buf;
};

template <>
inline void MemoryStream::write(bool data)
{
    writeBytes(&data, 1);
}

template <typename T>
inline void MemoryStream::write(T data)
{
    static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value);
    writeBytes(&data, sizeof(T));
}

template <>
inline void MemoryStream::read(bool& data)
{
    readBytes(&data, 1);
}

template <typename T>
inline void MemoryStream::read(T& data)
{
    static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value);
    readBytes(&data, sizeof(T));
}

template <typename T>
inline MemoryStream& MemoryStream::operator<<(T data)
{
    write(data);
    return *this;
}

template <typename T>
inline MemoryStream& MemoryStream::operator>>(T& data)
{
    read(data);
    return *this;
}
