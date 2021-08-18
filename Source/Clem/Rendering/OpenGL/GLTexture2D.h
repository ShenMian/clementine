// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Texture2D.h"
#include <unordered_map>

namespace clem
{

class GLTexture2D : public Texture2D
{
public:
    using handle_type = unsigned int;

    /**
	 * @brief 构造函数.
	 */
    GLTexture2D(const std::filesystem::path& path);

    /**
	 * @brief 默认析构函数.
	 */
    ~GLTexture2D();

    void load(const std::filesystem::path& path) override;
    void loadCubemap(const std::vector<std::filesystem::path>& faces) override;

    Size2i getSize() const override;
    size_t getHandle() override;

    void bind(unsigned int slot = 0) override;

private:
    handle_type handle_;
    Size2i      size;
    int         type;

    void* loadFromFile(const std::filesystem::path& path, int& width, int& height, int& channels);
};

} // namespace clem