
#include "clem/input/gamepad.h"

int main()
{
	Gamepad gamepad(0);

	while(true)
		gamepad.update();

	return 0;
}
