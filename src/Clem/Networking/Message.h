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
	std::vector<std::uint8_t> body;

	Message() = default;
	Message(T id)
	{
		header.id = id;
	}

	template <typename Data>
	friend Message<T>& operator<<(Message<T>& msg, const Data& data)
	{
		static_assert(std::is_standard_layout<Data>::value, "Data type is not suppoted");

		const auto offset = msg.body.size();
		msg.body.resize(msg.body.size() + sizeof(Data));
		msg.header.size = msg.body.size();
		std::memcpy(msg.body.data() + offset, &data, sizeof(Data));

		return msg;
	}

	template <typename Data>
	friend Message<T>& operator>>(Message<T>& msg, Data& data)
	{
		static_assert(std::is_standard_layout<Data>::value, "Data type is not suppoted");

		const auto offset = msg.body.size() - sizeof(Data);
		std::memcpy(&data, msg.body.data() + offset, sizeof(Data));
		msg.body.resize(msg.body.size() - sizeof(Data));
		msg.header.size = msg.body.size();

		return msg;
	}
};