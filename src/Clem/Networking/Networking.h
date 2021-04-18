// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Client.h"
#include "Server.h"

#include <cstdint>
#include <vector>

enum class PacketType
{
	connect,
	replication,
	disconnect
};

enum class ReplicationType
{
	position,
	velocity
};

template <typename T>
class Message
{
public:
	class Header;

	Header               header;
	std::vector<uint8_t> body;

	template <typename Data>
	friend Message<T>& operator<<(Message<T>& msg, const Data& data)
	{
		static_assert(std::is_standard_layout<Data>::value, "Data type is not suppoted");
	}
};

template <typename T>
class Message<T>::Header
{
public:
	T            id;
	std::uint8_t size;
};
