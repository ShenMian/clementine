// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

class Network
{
public:
	static void init();
	static void deinit();
};

#include <stdint.h>

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

/*

template <typename T>
class Message
{
public:
	class Header;

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
	uint8_t size;
};*/
