// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

#include "AL/alext.h"
#include <vector>
#include <filesystem>

// Warning: �����������Ƶ������ʼǰ��ʼ��, ���� OpenAL ���ᱨ��

class Audio
{
public:
	typedef ALuint id_t;

	static Audio& get();

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

	static void init();
	static void deinit();

private:
	Audio() = default;

	static std::vector<id_t> sounds;
	static ALCdevice*        device;
	static ALCcontext*       context;
};
