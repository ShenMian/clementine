// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Renderer.h"
#include <vulkan/vulkan.hpp>

namespace clem
{

class VKCommandBuffer;

/**
 * @addtogroup Rendering
 * @{
 */

class VKCommandPool
{
public:
  void create();
  void destroy();

  VKCommandBuffer allocateCommandBuffer();

  operator vk::CommandPool();

private:
  vk::CommandPool handle;
};

/**
* end of Rendering group
* @}
*/

} // namespace clem