// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "../Program.h"
#include <glad/glad.h>

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class GLProgram : public Program
{
public:
    explicit GLProgram(const std::string& name);
    virtual ~GLProgram();

private:
    GLuint handle;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem