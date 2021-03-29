// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <vector>
#include <filesystem>

// Warning: 务必在所以音频操作开始前初始化, 否则 OpenAL 不会报错

class Audio
{
public:
	typedef ALuint id_t;

	static Audio& get();

	/**
	 * @brief 加载声音.
	 * 
	 * @param path 声音文件路径.
	 * @return 声音ID
	 */
	id_t loadSound(const std::filesystem::path& path);

	/**
	 * @brief 卸载声音.
	 * 
	 * @param id 声音ID
	 * @return 成功 true, 失败 false
	 */
	bool unloadSound(id_t id);

private:
	Audio();
	~Audio();

	std::vector<id_t> sounds;

	ALCdevice*  device;
	ALCcontext* context;
};
