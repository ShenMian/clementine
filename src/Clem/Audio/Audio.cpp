// Copyright 2021 SMS
// License(Apache-2.0)

#include "Audio.h"
#include "Clem/Log.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <stdint.h>

#include <thread>

using namespace std::filesystem;

Audio& Audio::get()
{
	static Audio instance;
	return instance;
}

bool Audio::play(id_t id, float volume, float speed)
{
	static id_t currentId = 0;
	if(currentId != id)
	{
		alSourcei(source, AL_BUFFER, (ALint)id);
		currentId = id;
	}

	alSourcef(source, AL_GAIN, volume);
	alSourcef(source, AL_PITCH, speed);

	alSource3f(source, AL_POSITION, 0, 0, 0);
	
	alSourcePlay(source);

	/*auto err = alGetError();
	if(err != AL_NO_ERROR)
		CLEM_CORE_ERROR("OpenAL error: {}", alGetString(err));*/

	// alGetSourcef(source, AL_SEC_OFFSET, &offset);

	return true;
}

struct RiffHeader
{
	char    id[4]; // 资源交换文件标志
	int32_t size;
	char    format[4]; // WAV文件标志（WAVE）
};

struct WaveFormat
{
	char    id[4]; // 波形格式标志
	int32_t size;
	int16_t audioFormat;   // 音频格式
	int16_t numChannels;   // 声道数
	int32_t sampleRate;    // 采样率
	int32_t byteRate;      // 每秒数据字节数
	int16_t blockAlign;    // 数据块对齐
	int16_t bitsPerSample; // 采样位数
};

struct WaveData
{
	char    id[4];
	int32_t size;
};

Audio::id_t Audio::loadSound(const path& path)
{
	if(!exists(path))
		CLEM_CORE_CRITICAL("file does not exist: '{}'", path.string());

	std::ifstream file(path, std::ios::binary);
	if(!file.is_open())
		CLEM_CORE_CRITICAL("the file could not be opened: '{}'", path.string());

	RiffHeader riffHeader;
	file.read((char*)&riffHeader, sizeof(riffHeader));

	if((riffHeader.id[0] != 'R' ||
			riffHeader.id[1] != 'I' ||
			riffHeader.id[2] != 'F' ||
			riffHeader.id[3] != 'F') ||
		 (riffHeader.format[0] != 'W' ||
			riffHeader.format[1] != 'A' ||
			riffHeader.format[2] != 'V' ||
			riffHeader.format[3] != 'E'))
		CLEM_CORE_CRITICAL("invalid RIFF or WAVE Header: '{}'", path.string());

	WaveFormat waveFormat;
	WaveData   waveData;

	file.read((char*)&waveFormat, sizeof(waveFormat));

	if(waveFormat.size > 16)
		file.seekg(2, std::ios::cur);

	while(true)
	{
		char id[5] = {'\0'};

		file.read(id, 4);

		if(strcmp(id, "data") == 0)
		{
			file.seekg(-4, std::ios::cur);
			break;
		}
		else if(strcmp(id, "LIST") == 0)
			file.seekg(0x1E, std::ios::cur); // 格式转换信息
	}

	file.read((char*)&waveData, sizeof(waveData));
	
	/*if(waveFormat.id[0] != 'f' ||
		 waveFormat.id[1] != 'm' ||
		 waveFormat.id[2] != 't' ||
		 waveFormat.id[3] != ' ')
		CLEM_CORE_CRITICAL("invalid WAVE format: '{}'", path.string());

	if(waveFormat.size > 16)
		file.seekg(sizeof(short), std::ios::cur);*/

	/*if(waveData.id[0] != 'd' ||
		 waveData.id[1] != 'a' ||
		 waveData.id[2] != 't' ||
		 waveData.id[3] != 'a')
		CLEM_CORE_CRITICAL("invalid WAVE.DATA header: '{}'", path.string());*/

	ALenum  format    = 0;
	ALsizei size      = waveData.size;
	ALsizei frequency = waveFormat.sampleRate;

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
		CLEM_CORE_CRITICAL("invalid WAVE format: '{}'", path.string());

	auto data = new unsigned char[size];
	file.read((char*)data, size);

	id_t id;

	alGenBuffers(1, &id);
	alBufferData(id, format, (void*)data, size, frequency);
	assert(alGetError() == AL_NO_ERROR);

	delete[] data;
	file.close();

	sounds.push_back(id);

	return id;
}

bool Audio::unloadSound(id_t id)
{
	auto it = std::find(sounds.begin(), sounds.end(), id);
	if(it == sounds.end())
	{
		alDeleteBuffers(1, &id);
		sounds.erase(it);
		return true;
	}
	else
		return false;
}

Audio::Audio()
{
	device = alcOpenDevice(nullptr); // 获取默认设备
	assert(device);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);

	alGenSources(1, &source);
}

Audio::~Audio()
{
	alDeleteSources(1, &source);

	alDeleteBuffers(sounds.size(), sounds.data());
	sounds.clear();

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
