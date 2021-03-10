
#include <clem/platform.h>

#ifdef OS_UNIX
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	typedef int socket_t;
#endif // !OS_UNIX

#ifdef OS_WIN
	#include <winsock2.h>
	typedef SOCKET socket_t;
#endif // !OS_WIN
