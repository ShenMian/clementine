// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Editor.h"

int main()
{
	Editor::init();
	{
		Editor editor;
		editor.loop();
	}
	Editor::deinit();

	return 0;
}
