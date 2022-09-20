// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "Sound.h"
#include <AL/al.h>
#include <fstream>
#include <stdexcept>

#include <libnyquist/Decoders.h>

namespace fs = std::filesystem;

namespace
{

ALenum GetALFormat(int channelCount, int bitsPerSample)
{
	int format = -1;
	if(channelCount == 1)
	{
		if(bitsPerSample == 8)
			format = AL_FORMAT_MONO8;
		else if(bitsPerSample == 16)
			format = AL_FORMAT_MONO16;
	}
	else if(channelCount == 2)
	{
		if(bitsPerSample == 8)
			format = AL_FORMAT_STEREO8;
		else if(bitsPerSample == 16)
			format = AL_FORMAT_STEREO16;
	}
	if(format == -1)
		throw std::runtime_error("unknown audio format");
	return format;
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

void readWav(const fs::path& path, std::vector<uint8_t>& samples, uint32_t& sampleRate, uint16_t& channelCount,
             uint16_t& bitsPerSample)
{
	if(!fs::exists(path))
		throw std::runtime_error("no such file");

	std::ifstream file(path, std::ios::binary);
	if(!file.is_open())
		throw std::runtime_error("can not open file");

	RiffHeader riffHeader;
	file.read(reinterpret_cast<char*>(&riffHeader), sizeof(riffHeader));
	if(std::memcmp(riffHeader.id, "RIFF", 4) != 0 && std::memcmp(riffHeader.format, "WAVE", 4) != 0)
		throw std::runtime_error("incorrect file content");

	WaveFormat waveFormat;
	file.read((char*)&waveFormat, sizeof(waveFormat));
	if(waveFormat.size > 16)
		file.seekg(2, std::ios::cur);

	WaveData waveData;
	while(true)
	{
		if(!file.read((char*)&waveData, sizeof(waveData)))
			throw std::runtime_error("incorrect file content");

		if(std::memcmp(waveData.id, "data", 4) == 0)
		{
			samples.resize(waveData.size);
			file.read(reinterpret_cast<char*>(samples.data()), waveData.size);
			break;
		}
		else
		{
			file.seekg(waveData.size, std::ios::cur);
		}
	}

	file.close();

	sampleRate    = waveFormat.sampleRate;
	channelCount  = waveFormat.numChannels;
	bitsPerSample = waveFormat.bitsPerSample;
}

} // namespace

namespace audio
{

Sound::Sound(const fs::path& path)
{
	alGenBuffers(1, &handle);
	load(path);
}

Sound::~Sound()
{
	alDeleteBuffers(1, &handle);
}

void Sound::load(const fs::path& path)
{
	nqr::NyquistIO loader;
	if(!loader.IsFileSupported(path.string()))
		throw std::runtime_error("file format do not support");

	nqr::AudioData data;
	loader.Load(&data, path.string());

	// libnyquist 内部 BUG 临时解决方案
	if(data.frameSize == 32)
		data.frameSize = 4;
	else if(data.frameSize == 16)
		data.frameSize = 2;
	else
		data.frameSize = 4;

	const uint16_t bitsPerSample = (data.frameSize / data.channelCount) * 8;

	if(bitsPerSample == 8)
	{
		std::vector<uint8_t> buf(data.samples.size());
		std::transform(data.samples.begin(), data.samples.end(), buf.begin(),
		               [](float x) { return static_cast<uint8_t>((x * 127.f) + 128.f); });
		load(buf.data(), buf.size(), data.sampleRate, data.channelCount, bitsPerSample);
	}
	else if(bitsPerSample == 16)
	{
		std::vector<int16_t> buf(data.samples.size());
		std::transform(data.samples.begin(), data.samples.end(), buf.begin(),
		               [](float x) { return static_cast<int16_t>(x * std::numeric_limits<int16_t>::max()); });
		load(buf.data(), buf.size() * sizeof(int16_t), data.sampleRate, data.channelCount, bitsPerSample);
	}
	else
		throw std::runtime_error("unknown sample size");
}

void Sound::load(const void* data, size_t size, uint32_t sampleRate, uint16_t channelCount, uint16_t bitsPerSample)
{
	this->samplesCount  = size / (bitsPerSample / 8);
	this->sampleRate    = sampleRate;
	this->channelCount  = channelCount;
	this->bitsPerSample = bitsPerSample;

	alBufferData(handle, GetALFormat(channelCount, bitsPerSample), data, static_cast<ALsizei>(size), sampleRate);
}

} // namespace audio
