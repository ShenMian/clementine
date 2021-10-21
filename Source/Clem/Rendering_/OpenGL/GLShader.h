// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "../Shader.h"

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class GLShader_ : public Shader_
{
public:
    GLShader_(const std::string& name, Stage stage);
    virtual ~GLShader_();

    void load();

    size_t getNativeHandle() const override;

private:
    unsigned int handle;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem