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

class VKShader_ : public Shader_
{
public:
    VKShader_(const std::string& name, Stage stage);

    size_t getNativeHandle() const override;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem