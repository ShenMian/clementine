// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLRenderer.h"
#include "Clem/Logger.h"
#include <glad/glad.h>

namespace clem
{

void GLRenderer::init()
{
	CLEM_LOG_INFO("render", "Physical Device: {}", glGetString(GL_RENDERER));
}

void GLRenderer::deinit()
{
}

} // namespace clem