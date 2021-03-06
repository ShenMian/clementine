
#include <clem/platform.h>

#ifdef OS_UNIX
#include <sys/socket.h>
#endif // !OS_UNIX

#ifdef OS_WIN
#include <winsock2.h>
#endif // !OS_WIN
