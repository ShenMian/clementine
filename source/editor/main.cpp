// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "audio/device.h"
#include <Graphics.h>

int main()
{
	Renderer::setAPI(Renderer::API::OpenGL);
	Window::init();
	audio::Device::init();

	{
		Window window("Editor", {960, 540});
		Renderer::init(window);
		UI::init(window);

		window.setVisible(true);

		while(true)
		{
			window.update();
		}

		UI::deinit();
		Renderer::deinit();
	}

	audio::Device::deinit();
	Window::deinit();

	return 0;
}
