// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Components/Components.h"
#include "Core/Math/Math.h"
#include "ECS/Entity.h"
#include "Platform.h"

#ifdef OS_WIN
#    include <d3d12.h>
#endif

#include "Rendering_/Rendering.h"
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

    virtual void submit(const Entity& entity) = 0;

    virtual void submit(const Entity& entity, std::shared_ptr<Program> shader) = 0;

    virtual void submit(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Shader> shader, const Matrix4& transform) = 0;

    /**
     * @brief 新帧开始.
     */
    virtual void beginFrame() = 0;

    /**
     * @brief 新帧结束.
     */
    virtual void endFrame() = 0;

    /**
     * @brief 设置视口.
     *
     * @param x      视口 x 坐标.
     * @param y      视口 y 坐标.
     * @param width  视口宽度.
     * @param height 视口高度.
     */
    virtual void setViewport(int x, int y, int width, int height) = 0;

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