// Copyright 2020 SMS
// License(Apache-2.0)
// UDP Socket

#include "udp_socket.h"
#include "address.h"

using std::string;

bool UdpSocket::bind(const Address& addr)
{
	return ::bind(socket, &addr.getSockaddr(), addr.getSize());
}

void UdpSocket::write(const void* buf, size_t size, const Address& addr)
{
	auto n = sendto(socket, (char*)buf, size, 0, &addr.getSockaddr(), addr.getSize());
}

void UdpSocket::write(const string& buf, const Address& addr)
{
	write(buf.c_str(), buf.size(), addr);
}

void UdpSocket::read(void* buf, size_t size, const Address& addr)
{
}

void UdpSocket::read(string& buf, const Address& addr)
{
}
