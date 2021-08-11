// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Platform.h"

#ifdef OS_WIN
#    include <d3d12.h>
#endif

#include <memory>

namespace clem
{

class Shader;
class VertexArray;

/**
 * @addtogroup Rendering
 * @{
 */

class Renderer
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
	 * @brief 获取单例句柄.
	 *
	 * @return 单例句柄.
	 */
    static Renderer* get();

    /**
	 * @brief 设置图形 API.
	 *
	 * @param api 图形 API.
	 */
    static void setAPI(API api);

    /**
	 * @brief 获取图形 API.
	 *
	 * @return 图形 API.
	 */
    static API getAPI();

    /**
     * @brief 新帧开始.
     */
    virtual void beginFrame() = 0;

    /**
     * @brief 新帧结束.
     */
    virtual void endFrame()   = 0;

    virtual void submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader) = 0;

    virtual void init()   = 0;
    virtual void deinit() = 0;

private:
    static API       api;
    static Renderer* instance_;
};

/**
 * end of Rendering group
 * @}
 */

} // namespace clem