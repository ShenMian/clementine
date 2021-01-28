
#ifndef CLEM_WINDOWS_H_
#define CLEM_WINDOWS_H_

#include <windows.h>

class Windows
{
public:
	static HANDLE getOutHandle() const;

private:
	static HANDLE hStdOut;
};

#endif // CLEM_WINDOWS_H_

