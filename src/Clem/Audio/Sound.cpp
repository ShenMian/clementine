// Copyright 2021 SMS
// License(Apache-2.0)

#include "Sound.h"
#include "Clem/Assert.h"
#include "Clem/Log.h"
#include "Clem/Profiler.h"

using std::filesystem::exists;
using std::filesystem::path;

namespace clem
{
Sound::Sound()
{
	alGenBuffers(1, &id);
}

Sound::Sound(const path& path)
{
	alGenBuffers(1, &id);
	loadFromFile(path);
}

Sound::~Sound()
{
	alDeleteBuffers(1, &id);
}

void Sound::loadFromFile(const path& path)
{
	PROFILE_FUNC();

	Assert::isTrue(exists(path), fmt::format("file does not exist: '{}'", path.string()), CALL_INFO);

	auto fileName   = path.filename().string();
	auto fileFormat = fileName.substr(fileName.find_last_of('.'));

	ALenum         format;
	ALsizei        size;
	ALsizei        freq;
	unsigned char* data;

	if(fileFormat == ".wav")
		loadWavFile(path, format, data, size, freq);
	else
		CLEM_CORE_FATAL("unsupported file format: '{}'", fileFormat);

	alBufferData(id, format, (void*)data, size, freq);
	Assert::isTrue(alGetError() == AL_NO_ERROR, CALL_INFO);

	delete[] data;
}

Sound::operator id_t() const
{
	return id;
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

void Sound::loadWavFile(const std::filesystem::path& path, ALenum& format, unsigned char*& data, ALsizei& size, ALsizei& frequency)
{
	std::ifstream file(path, std::ios::binary);
	Assert::isTrue(file.is_open(), fmt::format("the file could not be opened: '{}'", path.string()), CALL_INFO);

	RiffHeader riffHeader;
	file.read((char*)&riffHeader, sizeof(RiffHeader));

	if(memcmp(riffHeader.id, "RIFF", 4) != 0 || memcmp(riffHeader.format, "WAVE", 4) != 0)
		CLEM_CORE_FATAL("invalid RIFF or WAVE Header: '{}'", path.string());

	WaveFormat waveFormat;
	WaveData   waveData;

	file.read((char*)&waveFormat, sizeof(WaveFormat));

	if(waveFormat.size > 16)
		file.seekg(2, std::ios::cur);

	char headId[5] = {'\0'};

	file.read(headId, 4);

	if(strcmp(headId, "LIST") == 0)
	{
		int32_t size;
		file.read((char*)&size, sizeof(size));
		file.seekg(size, std::ios::cur); // ���� ��ʽת����Ϣ
		file.read(headId, 4);
	}

	Assert::isTrue(strcmp(headId, "data") == 0, CALL_INFO);

	file.seekg(-4, std::ios::cur);
	file.read((char*)&waveData, sizeof(WaveData));

	format    = 0;
	size      = waveData.size;
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
	Assert::isTrue(format, fmt::format("invalid WAVE format: '{}'", path.string()), CALL_INFO);

	data = new unsigned char[size];

	file.read((char*)data, size);
	file.close();
}
} // namespace clem