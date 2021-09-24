// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Texture2D.h"
#include <glad/glad.h>
#include <unordered_map>

namespace clem
{

class GLTexture2D : public Texture2D
{
public:
    using handle_type = unsigned int;

    GLTexture2D();
    GLTexture2D(const Size2i& size, Format fmt = Format::Auto);
    GLTexture2D(const std::filesystem::path& path, bool genMipmap = true, Format fmt = Format::Auto);
    GLTexture2D(const void* data, Size2i size, int bits, bool genMipmap = true, Format fmt = Format::Auto);

    /**
	 * @brief 默认析构函数.
	 */
    ~GLTexture2D();

    void loadCubemap(const std::vector<std::filesystem::path>& faces) override;

    void setMinFilter(Filter filter) override;
    void setMagFilter(Filter filter) override;
    void setSWarp(Warp warp) override;
    void setTWarp(Warp warp) override;

    size_t getHandle() const override;

    void bind(unsigned int slot = 0) const override;

private:
    void  init(const void* data, Size2i size, int bits, bool genMipmap, Format fmt);
    void* loadFromFile(const std::filesystem::path& path, int& width, int& height, int& bits);

    handle_type handle;
    int         glType;

    static uint32_t GLInternalFormat(Format fmt);
    static uint32_t GLFormat(Format fmt);
};

} // namespace clem