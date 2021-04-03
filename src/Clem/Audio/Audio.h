// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <vector>
#include <filesystem>

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

	static void init();
	static void deinit();

private:
	Audio() = default;

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

	static std::vector<id_t> sounds;
	static ALCdevice*        device;
	static ALCcontext*       context;
};
