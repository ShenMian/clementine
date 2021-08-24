// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Texture2D.h"
#include <unordered_map>
#include <glad/glad.h>

namespace clem
{

class GLTexture2D : public Texture2D
{
public:
    using handle_type = unsigned int;

    /**
	 * @brief 默认构造函数.
	 */
    static std::shared_ptr<Texture2D> create();

    /**
	 * @brief 构造函数.
     *
     * @param path 文件路径.
	 */
    static std::shared_ptr<Texture2D> create(const std::filesystem::path& path, Format format = Format::Auto);

    /**
	 * @brief 默认析构函数.
	 */
    ~GLTexture2D();

    void load(const std::filesystem::path& path, Format format = Format::Auto) override;
    void loadCubemap(const std::vector<std::filesystem::path>& faces) override;

    void setMinFilter(Filter filter) override;
    void setMagFilter(Filter filter) override;

    Size2i getSize() const override;
    size_t getHandle() override;

    void bind() override;

    void bindUnit(unsigned int slot = 0) override;

    GLTexture2D();
    GLTexture2D(const std::filesystem::path& path);

private:
    handle_type handle;
    Size2i      size;
    int         glType;

    void* loadFromFile(const std::filesystem::path& path, int& width, int& height, int& bits);
};

} // namespace clem