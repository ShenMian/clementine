// Copyright 2021 SMS
// License(Apache-2.0)

#include "SoundBuffer.h"
#include "AL/alext.h"
#include <fstream>

namespace clem
{

SoundBuffer::SoundBuffer()
{
	alGenBuffers(1, &id);
}

SoundBuffer::~SoundBuffer()
{
	alDeleteBuffers(1, &id);
}

bool SoundBuffer::loadFromFile(const std::filesystem::path& path)
{
	if(!std::filesystem::exists(path))
		return false;

	auto name      = path.filename().string();
	auto extension = name.substr(name.find_last_of('.') + 1);

	ALenum  format;
	ALsizei size;
	ALsizei freq;

	bool ret;

	if(extension == "wav")
		ret = loadWavFile(path);
	else
		ret = false;

	return ret;
}

const uint8_t* SoundBuffer::getSamples() const
{
	return samples.data();
}

size_t SoundBuffer::getSampleCount() const
{
	return samples.size();
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

bool SoundBuffer::loadWavFile(const std::filesystem::path& path)
{
	std::ifstream file(path, std::ios::binary);
	if(!file.is_open())
		return false;

	RiffHeader riffHeader;
	WaveFormat waveFormat;
	WaveData   waveData;

	file.read((char*)&riffHeader, sizeof(RiffHeader));
	if(memcmp(riffHeader.id, "RIFF", 4) != 0 || memcmp(riffHeader.format, "WAVE", 4) != 0)
		return false;

	file.read((char*)&waveFormat, sizeof(WaveFormat));
	if(waveFormat.size > 16)
		file.seekg(2, std::ios::cur);

	char id[4];
	file.read(id, 4);

	// ��� WAV �ļ�����������ʽת������, ����� ID Ϊ LIST �ĸ�ʽת����Ϣ.
	// �����ⲿ������, ֱ�ӻ�ȡ��Ƶ��������.
	if(memcmp(id, "LIST", 4) == 0)
	{
		int32_t list_size;
		file.read((char*)&list_size, sizeof(list_size));
		file.seekg(list_size, std::ios::cur);
		file.read(id, 4);
	}

	if(memcmp(id, "data", 4) != 0)
		return false;

	file.seekg(-4, std::ios::cur);
	file.read((char*)&waveData, sizeof(WaveData));

	format    = 0;
	frequency = waveFormat.sampleRate;

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
		return false;

	samples.resize(waveData.size);
	file.read((char*)samples.data(), waveData.size);
	file.close();
}

} // namespace clem
