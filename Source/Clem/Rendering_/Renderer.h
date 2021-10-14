// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

namespace clem
{

/**
 * @addtogroup Rendering
 * @{
 */

class Renderer_
{
public:
    enum class API
    {
        OpenGL,
        Vulkan,
        D3D12,
        Metal
    };

    /**
	 * @brief 设置图形 API.
	 *
	 * @param api 图形 API.
	 */
    static void setAPI(API api);

    /**
	 * @brief 获取图形 API.
	 */
    static API getAPI();

private:
    static API api;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem