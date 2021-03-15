// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_PROFILER_H_
#define CLEM_PROFILER_H_

#include <chrono>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

struct ProfileRecord
{
	std::string                               name;
	std::chrono::duration<double, std::micro> start;
	std::chrono::microseconds                 elapsed;
	std::thread::id                           threadId;
};

class Instrumentor
{
public:
	static Instrumentor& getInstance();

	void begin(const char* filepath = "profile.json");
	void end();

	void writeRecord(const ProfileRecord& record);

private:
	~Instrumentor();
	void writeHead();
	void writeFooter();

	std::mutex    mutex;
	std::ofstream file;
	bool          session = false;
};

class InstrumentationCounter
{
public:
	InstrumentationCounter(const char* name);
	~InstrumentationCounter();

	void stop();

private:
	const char*                                        name;
	bool                                               stopped;
	std::chrono::time_point<std::chrono::steady_clock> begin;
};

#define PROFILE_SESSION_BEGIN(filepath) Instrumentor::getInstance().begin(filepath)
#define PROFILE_SESSION_END() Instrumentor::getInstance().end()
#define PROFILE_SCOPE(name) InstrumentationCounter counter##__LINE__(name)
#define PROFILE_FUNC() PROFILE_SCOPE(__FUNCTION__)
// #define PROFILE_FUNC() PROFILE_SCOPE(__FUNCSIG__)

#define PROFILE_SCOPE_BEGIN(name) \
	{                               \
		PROFILE_SCOPE(name)
#define PROFILE_SCOPE_END() }

#endif // !CLEM_PROFILER_H_
