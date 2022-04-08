#include <Graphics.h>
#include <Core/Time.hpp>
#include <Audio/Sound.h>
#include <Audio/Source.h>
#include <Audio/Listener.h>
#include <Audio/Audio.h>

using namespace core;
using namespace audio;

int main()
{
	auto prev = std::chrono::high_resolution_clock::now();
	while(true)
	{
		const auto curr = std::chrono::high_resolution_clock::now();
		const auto elapsed = curr - prev;
		prev = curr;
	}

	return 0;
}
