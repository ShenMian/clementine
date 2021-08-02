// Copyright 2021 SMS
// License(Apache-2.0)

#include "Sound.h"
#include "AL/alext.h"
#include "Clem/Assert.h"
#include "Clem/Logger.h"
#include "Clem/Profiler.h"
#include <cassert>
#include <fstream>

namespace fs = std::filesystem;

namespace clem
{

Sound::Sound()
{
	alGenBuffers(1, &bufferId);
}

Sound::Sound(const fs::path& path)
{
	alGenBuffers(1, &bufferId);
	loadFromFile(path);
}

Sound::~Sound()
{
	alDeleteBuffers(1, &bufferId);
}

void Sound::loadFromFile(const fs::path& path)
{
	PROFILE_FUNC();

	Assert::isTrue(fs::exists(path), std::format("file doesn't exist: '{}'", path.string()));

	const auto extension = path.extension().string();
	if(extension == ".wav")
		loadWavFile(path);
	else
		Assert::isTrue(false, std::format("file extension doesn't supported: '{}'", extension));

	CLEM_LOG_INFO("audio", "sound loaded from file: '{}'", path.string());

	initialized = true;
}

const uint8_t* Sound::getSamples() const
{
	assert(initialized);
	return samples.data();
}

size_t Sound::getSampleCount() const
{
	assert(initialized);
	return samples.size() * 8 / bitsPerSample;
}

unsigned int Sound::getSampleRate() const
{
	assert(initialized);
	return sampleRate;
}

unsigned int Sound::getChannelCount() const
{
	assert(initialized);
	return channelCount;
}

size_t Sound::getTime() const
{
	assert(initialized);
	return getSampleCount() / (getChannelCount() * getSampleRate());
}

int32_t Sound::getBufferId() const
{
	assert(initialized);
	return bufferId;
}

struct RiffHeader
{
	char    id[4];     // ��Դ�����ļ���־, "RIFF"
	int32_t size;      // �ļ��ܴ�С
	char    format[4]; // WAV �ļ���־
};

struct WaveFormat
{
	char    id[4];         // ���θ�ʽ��־, "WAVE"
	int32_t size;          // ��С
	int16_t audioFormat;   // ��Ƶ��ʽ, ���� PCM ����
	int16_t numChannels;   // ������
	int32_t sampleRate;    // ������, Hz
	int32_t byteRate;      // �������ݴ�����, Bps
	int16_t blockAlign;    // �����
	int16_t bitsPerSample; // ����λ��
};

struct WaveData
{
	char    id[4];
	int32_t size;
};

void Sound::loadWavFile(const fs::path& path)
{
	std::ifstream file(path, std::ios::binary);
	Assert::isTrue(file.is_open(), std::format("can't open file: {}", path.string()));

	RiffHeader riffHeader;
	WaveFormat waveFormat;
	WaveData   waveData;

	file.read((char*)&riffHeader, sizeof(RiffHeader));
	Assert::isTrue(std::memcmp(riffHeader.id, "RIFF", 4) == 0 && std::memcmp(riffHeader.format, "WAVE", 4) == 0, "incorrect file content");

	file.read((char*)&waveFormat, sizeof(WaveFormat));
	if(waveFormat.size > 16)
		file.seekg(2, std::ios::cur);

	char id[4];
	file.read(id, 4);

	// ��� WAV �ļ�����������ʽת������, ����� ID Ϊ LIST �ĸ�ʽת����Ϣ.
	// �����ⲿ������, ֱ�ӻ�ȡ��Ƶ��������.
	if(std::memcmp(id, "LIST", 4) == 0)
	{
		int32_t list_size;
		file.read((char*)&list_size, sizeof(list_size));
		file.seekg(list_size, std::ios::cur);
		file.read(id, 4);
	}

	Assert::isTrue(std::memcmp(id, "data", 4) == 0, "incorrect file content");

	file.seekg(-4, std::ios::cur);
	file.read((char*)&waveData, sizeof(WaveData));

	sampleRate    = waveFormat.sampleRate;
	channelCount  = waveFormat.numChannels;
	bitsPerSample = waveFormat.bitsPerSample;

	int format = -1;
	if(waveFormat.numChannels == 1)
	{
		if(waveFormat.bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if(waveFormat.bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
	}
	else if(waveFormat.numChannels == 2)
	{
		if(waveFormat.bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if(waveFormat.bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
	}
	Assert::isTrue(format != -1, "unknown audio format");

	samples.resize(waveData.size);
	file.read((char*)samples.data(), waveData.size);

	file.close();

	alBufferData(bufferId, format, (void*)samples.data(), (ALsizei)samples.size(), sampleRate);
}

} // namespace clem