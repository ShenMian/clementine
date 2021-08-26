// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Core/Math/Math.h"
#include "Rendering/Texture2D.h"
#include <memory>
#include <vector>

namespace clem
{

/**
 * @brief 帧缓冲区.
 */
class FrameBuffer
{
public:
    using PixelFormat = Texture2D::Format;

    /**
     * @brief 创建帧缓冲区.
     * 
     * @param size    缓冲区大小.
     * @param formats .
     * @param samples .
     * @return std::shared_ptr<FrameBuffer> 
     */
    static std::shared_ptr<FrameBuffer> create(Size2i size, const std::vector<PixelFormat>& formats, int samples = 1);

    /**
     * @brief 获取指定颜色渲染目标.
     * 
     * @param index 颜色渲染目标索引.
     */
    virtual std::shared_ptr<Texture2D> getColorAttachment(int index = 0) = 0;

    /**
     * @brief 获取颜色渲染目标.
     */
    virtual std::shared_ptr<Texture2D> getDepthAttachment() = 0;

    /**
     * @brief 初始化颜色渲染目标.
     * 
     * @param index 颜色渲染目标索引.
     * @param value 初始化的值.
     */
    virtual void clearColorAttachment(int index, int value) = 0;

    /**
     * @brief 获取帧缓冲区大小.
     */
    virtual Size2i getSize() const;

    /**
     * @brief 获取指定颜色渲染目标中某个像素的值.
     * 
     * @param index 颜色渲染目标索引.
     * @param pos   像素坐标.
     * @param data  像素数据.
     */
    virtual void read(int index, Vector2i pos, int& data) = 0;

    virtual void bind()   = 0;
    virtual void unbind() = 0;

protected:
    Size2i                                  size;
    std::vector<std::shared_ptr<Texture2D>> colorAttachments;
    std::shared_ptr<Texture2D>              depthAttachments;
};

} // namespace clem