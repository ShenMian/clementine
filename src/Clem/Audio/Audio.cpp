// Copyright 2021 SMS
// License(Apache-2.0)

#include "Audio.h"
#include "Clem/Log.h"
#include "Clem/Profiler.h"
#include <cassert>
#include <fstream>
#include <stdint.h>

using namespace std::filesystem;

std::vector<Audio::id_t> Audio::sounds;
ALCdevice*               Audio::device;
ALCcontext*              Audio::context;

Audio& Audio::get()
{
	static Audio instance;
	return instance;
}

Audio::id_t Audio::loadSound(const path& path)
{
	PROFILE_FUNC();

	if(!exists(path))
		CLEM_CORE_FATAL("file does not exist: '{}'", path.string());

	auto fileName = path.filename().string();
	auto fileFormat = fileName.substr(fileName.find_last_of('.'));

	ALenum         format;
	ALsizei        size;
	ALsizei        frequency;
	unsigned char* data;

	if(fileFormat == ".wav")
		loadWav(path, format, data, size, frequency);
	else
		CLEM_CORE_FATAL("unsupported file format: '{}'", fileFormat);

	id_t id;
	alGenBuffers(1, &id);
	alBufferData(id, format, (void*)data, size, frequency);
	assert(alGetError() == AL_NO_ERROR);

	delete[] data;

	sounds.push_back(id);

	return id;
}

bool Audio::unloadSound(id_t id)
{
	PROFILE_FUNC();

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

struct RiffHeader
{
	char    id[4];     // 资源交换文件标志, "RIFF"
	int32_t size;      // 文件总大小
	char    format[4]; // WAV 文件标志
};

struct WaveFormat
{
	char    id[4];         // 波形格式标志, "WAVE"
	int32_t size;          // 大小
	int16_t audioFormat;   // 音频格式, 线性 PCM 编码
	int16_t numChannels;   // 声道数
	int32_t sampleRate;    // 采样率, Hz
	int32_t byteRate;      // 波形数据传输率, Bps
	int16_t blockAlign;    // 块对齐
	int16_t bitsPerSample; // 采样位数
};

struct WaveData
{
	char    id[4];
	int32_t size;
};

void Audio::loadWav(const path& path, ALenum& format, unsigned char*& data, ALsizei& size, ALsizei& frequency)
{
	std::ifstream file(path, std::ios::binary);
	if(!file.is_open())
		CLEM_CORE_FATAL("the file could not be opened: '{}'", path.string());

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
		CLEM_CORE_FATAL("invalid RIFF or WAVE Header: '{}'", path.string());

	WaveFormat waveFormat;
	WaveData   waveData;

	file.read((char*)&waveFormat, sizeof(waveFormat));

	if(waveFormat.size > 16)
		file.seekg(2, std::ios::cur);

	char headId[5] = {'\0'};

	file.read(headId, 4);

	if(strcmp(headId, "LIST") == 0)
	{
		int32_t size;
		file.read((char*)&size, sizeof(size));
		file.seekg(size, std::ios::cur); // 跳过 格式转换信息
		file.read(headId, 4);
	}

	assert(strcmp(headId, "data") == 0);

	file.seekg(-4, std::ios::cur);
	file.read((char*)&waveData, sizeof(waveData));

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
	if(format == 0)
		CLEM_CORE_FATAL("invalid WAVE format: '{}'", path.string());

	data = new unsigned char[size];

	file.read((char*)data, size);
	file.close();
}

void Audio::init()
{
	PROFILE_FUNC();

	device = alcOpenDevice(nullptr); // 获取默认设备
	assert(device);
	context = alcCreateContext(device, nullptr);
	alcMakeContextCurrent(context);
}

void Audio::deinit()
{
	PROFILE_FUNC();

	alDeleteBuffers((ALsizei)sounds.size(), sounds.data());
	sounds.clear();

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
