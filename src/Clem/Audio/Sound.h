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
	 * @brief Ĭ�Ϲ��캯��.
	 */
	Sound();

	/**
	 * @brief ���캯��, ���ļ���������.
	 */
	Sound(const std::filesystem::path&);

	/**
	 * @brief ��������, ж������.
	 */
	~Sound();

	/**
	 * @brief ��������.
	 * 
	 * @param path �����ļ�·��.
	 */
	void loadFromFile(const std::filesystem::path&);

	operator id_t() const;

private:
	/**
	 * �� WAV �ļ���������.
	 * 
	 * @param path      �ļ�·��
	 * @param format    ��ʽ
	 * @param data      �������ݻ�����
	 * @param size      �������ݻ�������С
	 * @param frequency ����Ƶ��
	 */
	void loadWav(const std::filesystem::path& path, ALenum& format, unsigned char*& data, ALsizei& size, ALsizei& frequency);

	 id_t id;
};
