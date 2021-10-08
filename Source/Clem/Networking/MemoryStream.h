// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>

class MemoryStream
{
public:
    template <typename T>
    void write(T value);

    void writeBytes(const void* data, size_t size);

    void writeBits(const void* data, size_t size);

    template <typename T>
    void read(T& value);

    void readBytes(void* data, size_t size);

    void readBits(void* data, size_t size);

    size_t byteSize() const;
    size_t bitSize() const;

private:
    size_t              size = 0;
    std::vector<int8_t> buf;
};

template <>
inline void MemoryStream::write(bool value)
{
    writeBytes(&value, 1);
}

template <typename T>
inline void MemoryStream::write(T value)
{
    static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value);
    writeBytes(&value, sizeof(T));
}

template <>
inline void MemoryStream::read(bool& value)
{
    readBytes(&value, 1);
}

template <typename T>
inline void MemoryStream::read(T& value)
{
    static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value);
    readBytes(&value, sizeof(T));
}
