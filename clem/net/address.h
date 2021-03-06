// Copyright 2020 SMS
// License(Apache-2.0)
// IPµÿ÷∑

#ifndef CLEM_NET_ADDRESS_H_
#define CLEM_NET_ADDRESS_H_

#include "header.h"
#include <string>

class Address
{
public:
	Address(const std::string& addr);

	const sockaddr& getSockaddr() const;
	size_t          getSize() const;

private:
	sockaddr address;
};

#endif // !CLEM_NET_ADDRESS_H_
