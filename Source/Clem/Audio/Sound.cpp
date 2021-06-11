// Copyright 2021 SMS
// License(Apache-2.0)

#include "Sound.h"
#include "AL/alext.h"
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
	if(!fs::exists(path))
		return; // file doesn't exist

	auto name      = path.filename().string();
	auto extension = name.substr(name.find_last_of('.') + 1);

	if(extension == "wav")
		loadWavFile(path);
	else
		return; // unsupported file extension
}

const uint8_t* Sound::getSamples() const
{
	return samples.data();
}

size_t Sound::getSampleCount() const
{
	return samples.size();
}

int32_t Sound::getBufferId() const
{
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
	if(!file.is_open())
		return; // can't open file

	RiffHeader riffHeader;
	WaveFormat waveFormat;
	WaveData   waveData;

	file.read((char*)&riffHeader, sizeof(RiffHeader));
	if(std::memcmp(riffHeader.id, "RIFF", 4) != 0 || std::memcmp(riffHeader.format, "WAVE", 4) != 0)
		return; // incorrect file content

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

	if(std::memcmp(id, "data", 4) != 0)
		return; // incorrect file content

	file.seekg(-4, std::ios::cur);
	file.read((char*)&waveData, sizeof(WaveData));

	sampleRate   = waveFormat.sampleRate;
	channelCount = waveFormat.numChannels;

	int format = 0;
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
	if(format == 0)
		return; // unknown audio format

	samples.resize(waveData.size);
	file.read((char*)samples.data(), waveData.size);

	file.close();

	alBufferData(bufferId, format, (void*)samples.data(), (ALsizei)samples.size(), sampleRate);
}
} // namespace clem