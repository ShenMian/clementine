#include "KeyEvent.h"

KeyEvent::KeyEvent(short keyCode, bool state, short repeatCount)
		: keyCode(keyCode), state(state), repeatCount(repeatCount)
{
}