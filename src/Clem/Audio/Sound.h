// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <filesystem>

class Sound
{
public:
	typedef ALuint id_t;

	/**
	 * @brief 默认构造函数.
	 */
	Sound();

	/**
	 * @brief 构造函数, 从文件导入声音.
	 */
	Sound(const std::filesystem::path&);

	/**
	 * @brief 析构函数, 卸载声音.
	 */
	~Sound();

	/**
	 * @brief 加载声音.
	 * 
	 * @param path 声音文件路径.
	 */
	void loadFromFile(const std::filesystem::path&);

	operator id_t() const;

private:
	/**
	 * 从 WAV 文件载入声音.
	 * 
	 * @param path      文件路径
	 * @param format    格式
	 * @param data      声音数据缓冲区
	 * @param size      声音数据缓冲区大小
	 * @param frequency 声音频率
	 */
	void loadWav(const std::filesystem::path& path, ALenum& format, unsigned char*& data, ALsizei& size, ALsizei& frequency);

	 id_t id;
};
