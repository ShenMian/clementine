// Copyright 2021 SMS
// License(Apache-2.0)

#include "Program.h"
#include "Renderer.h"
#include <cassert>

#include "OpenGL/GLProgram.h"

namespace clem
{

std::shared_ptr<Program> Program::create(const std::string& name)
{
    switch(Renderer_::getAPI())
    {
        using enum Renderer_::API;

    case OpenGL:
        return std::make_shared<GLProgram>(name);

    default:
        assert(false);
    }
    return nullptr;
}

Program::Program(const std::string& name)
    : name(name)
{
}

} // namespace clem