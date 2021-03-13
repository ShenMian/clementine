// Copyright 2021 SMS
// License(Apache-2.0)
// UDP Socket

#ifndef CLEM_NET_UDP_SOCKET_H_
#define CLEM_NET_UDP_SOCKET_H_

#include <string>

class Address;

class UdpSocket
{
public:
	bool bind(const Address& addr);

	void write(const void* buf, size_t size, const Address& addr);
	void write(const std::string& buf, const Address& addr);

	void read(void* buf, size_t size, const Address& addr);
	void read(std::string& buf, const Address& addr);

private:
	socket_t socket;
};

#endif // !CLEM_NET_UDP_SOCKET_H_
