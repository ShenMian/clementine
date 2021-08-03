// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "Rendering/Texture2D.h"

namespace clem
{

class GLTexture2D : public Texture2D
{
public:
	using id_type = unsigned int;

	/**
	 * @brief 构造函数.
	 */
	GLTexture2D(const std::filesystem::path& path);

	/**
	 * @brief 默认析构函数.
	 */
	~GLTexture2D();

	void          bind(id_type slot) override;
	virtual void* nativeHandle() override;

private:
	id_type handle;

	void* loadFromFile(const std::filesystem::path& path, int& width, int& height, int& channels);
};

} // namespace clem