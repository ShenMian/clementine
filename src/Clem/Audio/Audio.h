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

	bool play(id_t id, float volume = 1.0f, float speed = 1.0f);

	/**
	 * @brief ��������.
	 * 
	 * @param path �����ļ�·��.
	 * @return ����ID
	 */
	id_t loadSound(const std::filesystem::path& path);

	/**
	 * @brief ж������.
	 * 
	 * @param id ����ID
	 * @return �ɹ� true, ʧ�� false
	 */
	bool unloadSound(id_t id);

private:
	Audio();
	~Audio();

	id_t              source = 0;
	std::vector<id_t> sounds;

	ALCdevice*  device;
	ALCcontext* context;
};
