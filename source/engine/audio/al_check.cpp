// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "al_check.h"
#include <AL/al.h>
#include <stdexcept>
#include <string>

namespace
{

std::string_view ALGetErrorString(ALenum error)
{
	switch(error)
	{
	case AL_INVALID_NAME:
		return "AL_INVALID_NAME";

	case AL_INVALID_ENUM:
		return "AL_INVALID_ENUM";

	case AL_INVALID_VALUE:
		return "AL_INVALID_VALUE";

	case AL_INVALID_OPERATION:
		return "AL_INVALID_OPERATION";

	case AL_OUT_OF_MEMORY:
		return "AL_OUT_OF_MEMORY";

	default:
		return "Unknown";
	}
}

std::string_view ALGetErrorDescString(ALenum error)
{
	switch(error)
	{
	case AL_INVALID_NAME:
		return "A bad name (ID) has been specified.";

	case AL_INVALID_ENUM:
		return "An unacceptable value has been specified for an enumerated argument.";

	case AL_INVALID_VALUE:
		return "A numeric argument is out of range.";

	case AL_INVALID_OPERATION:
		return "The specified operation is not allowed in the current state.";

	case AL_OUT_OF_MEMORY:
		return "There is not enough memory left to execute the command.";

	default:
		return "Unknown";
	}
}

} // namespace

namespace audio
{

void ALCheckError()
{
	while(const auto error = alGetError())
		throw std::runtime_error(ALGetErrorString(error).data());
}

void ALClearError()
{
	while(alGetError() != AL_NO_ERROR)
		;
}

} // namespace audio
