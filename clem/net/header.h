
#include <clem/platform.h>

#ifdef OS_UNIX
#include <sys/socket.h>
typedef int socket_t;
#endif // !OS_UNIX

#ifdef OS_WIN
#include <winsock2.h>
typedef SOCKET socket_t;
#endif // !OS_WIN
