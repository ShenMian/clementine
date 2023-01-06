// Copyright 2022 ShenMian
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <cstring>
#include <type_traits>
#include <vector>

namespace core
{

class MemoryStream
{
public:
	void write(const void* data, size_t size)
	{
		this->data.resize(this->data.size() + size);
		std::memcpy(this->data.data(), data, size);
	}

	void read(void* data, size_t size)
	{
		check(size <= this->data.size());
		std::memcpy(data, this->data.data(), size);
		this->data.resize(this->data.size() - size);
	}

	// void writeBits(uint8_t data, uint8_t count);
	// void readBits();

	template <typename T>
	    requires std::is_arithmetic_v<T>
	void write(const T& data)
	{
		write(&data, sizeof(T));
	}

	size_t sizeBytes() const;
	size_t sizeBits() const;

private:
	std::vector<uint8_t> data;
};

} // namespace core
