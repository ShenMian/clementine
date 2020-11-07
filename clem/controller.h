
#include <vector>

typedef unsigned short ushort;

class Controller
{
public:
	enum Key
	{
	};

	Controller();

	bool isConnected() const;
	
private:
	ushort port;
	bool   connected;

	static std::vector<Controller*> controllers;
};

