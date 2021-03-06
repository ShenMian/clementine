// Copyright 2020 SMS
// License(Apache-2.0)
// IPµÿ÷∑

#include "address.h"

using std::string;

Address::Address(const string& addr)
{
}

const sockaddr& Address::getSockaddr() const
{
	return address;
}

size_t Address::getSize() const
{
	return sizeof(address);
}
