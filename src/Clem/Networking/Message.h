// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include <cstdint>
#include <vector>

template <typename T>
class Message
{
public:
	struct
	{
		T            id;
		std::uint8_t size = 0;
	} header;

	std::vector<uint8_t> body;

	Message(T id)
	{
		header.id = id;
	}

	template <typename Data>
	friend Message<T>& operator<<(Message<T>& msg, const Data& data)
	{
		static_assert(std::is_standard_layout<Data>::value, "Data type is not suppoted");
	}
};