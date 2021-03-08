
#include "terminal.h"
#include <cassert>
#include "platform.h"

#ifdef OS_LINUX

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cerrno>

void Terminal::setTitle(const std::string&)
{
}

bool Terminal::getch(char& c)
{
  char buf[1];
  int  n;

  n = read(STDIN_FILENO, buf, 1);
  if(n == -1 && errno != EAGAIN)
    assert(false);
  if(n != 1)
    return false;
  c = buf[0];
  return true;
}

#endif // !OS_LINUX

#ifdef OS_WIN

#include <windows.h>

#include <conio.h>

void Terminal::setTitle(const std::string& str)
{
	SetConsoleTitleA(str.c_str());
}

bool Terminal::getch(char& c)
{
  char  buf[1];
  DWORD n;

  if(!_kbhit())
    return false;
  if(!ReadFile(GetStdHandle(STD_INPUT_HANDLE), buf, 1, &n, nullptr))
    assert(false);
  if(n != 1)
    assert(false);
  c = buf[0];
  return true;
}

#endif // !OS_WIN

