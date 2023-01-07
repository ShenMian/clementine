// Copyright 2022 ShenMian
// License(Apache-2.0)

#include "sound.hpp"
#include <AL/al.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <libnyquist/Decoders.h>
#include <optional>
#include <stdexcept>

namespace fs = std::filesystem;

namespace
{

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

[[deprecated]] void readWav(const fs::path& path, std::vector<uint8_t>& samples, uint32_t& sampleRate,
                            uint16_t& channelCount, uint16_t& bitsPerSample)
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
