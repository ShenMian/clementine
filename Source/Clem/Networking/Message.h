// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Clem/Assert.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace clem
{

/**
 * @addtogroup Networking
 * @{
 */

/**
 * @brief 网络消息.
 * 
 * @tparam T 消息 ID 类型, 强类型枚举体.
 */
template <typename T>
class Message
{
public:
	struct
	{
		T       id;
		uint8_t size = 0;
	} header;
	std::vector<std::byte> body;

	Message() = default;
	Message(T id)
	{
		header.id = id;
	}

	template <typename Data>
	friend Message<T>& operator<<(Message<T>& msg, const Data& data)
	{
		static_assert(std::is_standard_layout<Data>::value, "Data type is not suppoted");
		ASSERT_TRUE(msg.header.size < (size_t)-1 - sizeof(Data), "Message is full");

		const auto offset = msg.body.size();
		msg.body.resize(msg.body.size() + sizeof(Data));
		std::memcpy(msg.body.data() + offset, &data, sizeof(Data));
		msg.header.size = (uint8_t)msg.body.size();

		return msg;
	}

	template <typename Data>
	friend Message<T>& operator>>(Message<T>& msg, Data& data)
	{
		static_assert(std::is_standard_layout<Data>::value, "Data type is not suppoted");

		const auto offset = msg.body.size() - sizeof(Data);
		std::memcpy(&data, msg.body.data() + offset, sizeof(Data));
		msg.body.resize(msg.body.size() - sizeof(Data));
		msg.header.size = (uint8_t)msg.body.size();

		return msg;
	}

	template <typename Data>
	friend Message<T>& operator<<(Message<T>& msg, const std::vector<Data>& data)
	{
		ASSERT_TRUE(msg.header.size < (size_t)-1 - data.size() * sizeof(Data), "Message is full");

		for(const auto& i : data)
			msg << i;
		msg << data.size();
		return msg;
	}

	template <typename Data>
	friend Message<T>& operator>>(Message<T>& msg, std::vector<Data>& data)
	{
		size_t size;
		msg >> size;
		data.resize(size);
		for(auto& i : data)
			msg >> i;
		return msg;
	}
};

/**
 * end of Networking group
 * @}
 */

} // namespace clem