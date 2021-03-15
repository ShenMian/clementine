// Copyright 2021 SMS
// License(Apache-2.0)

#include "director.h"
#include "log.h"
#include "platform.h"
#include "profiler.h"
#include "scene.h"
#include <cassert>
#include <chrono>

using std::chrono::milliseconds;
using std::this_thread::sleep_for;

Director Director::instance;

Director* Director::getInstance()
{
	return &instance;
}

/**
 * @brief 在单独的线程中启动主循环.
 */
void Director::run()
{
	if(scenes.empty())
	{
		CLEM_ENGINE_ERROR("Lunch main loop when the scenes is empty");
		return;
	}

	running = true;
	thread  = std::thread(&Director::loop, this);
}

void Director::stop()
{
	running = false;
	assert(thread.joinable());
	thread.join();
}

/**
 * @brief 暂停主循环.
 */
void Director::pause()
{
	paused = true;
}

/**
 * @brief 恢复主循环.
 */
void Director::resume()
{
	paused = false;
}

/**
 * @brief 压入场景.
 * 
 * @param s 要压入的场景.
 */
void Director::pushScene(Scene& s)
{
	scenes.push_back(&s);
}

/**
 * @brief 弹出场景.
 */
void Director::popScene()
{
	if(scenes.empty())
	{
		CLEM_ENGINE_ERROR("Pop a scene when the scenes is empty");
		return;
	}
	scenes.pop_back();
}

/**
 * @brief 替换场景.
 * 
 * @param s 要替换的场景.
 */
void Director::replaceScene(Scene& s)
{
	if(scenes.empty())
	{
		CLEM_ENGINE_ERROR("Replace a scene when the scenes is empty");
		return;
	}
	scenes.front() = &s;
}

/**
 * @brief 获取当前场景.
 * 
 * @return Scene* 当前场景.
 */
Scene* Director::getCurrentScene() const
{
	if(!scenes.empty())
		return scenes.back();
	else
		return nullptr;
}

/**
 * @brief 设置更新时间周期.
 * 
 * @param ms 更新时间周期(ms).
 */
void Director::setMsPerUpdate(long ms)
{
	if(ms <= 0)
	{
		CLEM_ENGINE_CRITICAL("Set ms per update non positive");
		assert(false);
	}
	msPerUpdate = ms;
}

/**
 * @brief 设置渲染时间周期.
 * 
 * @param ms 渲染时间周期(ms).
 */
void Director::setMsPerRender(long ms)
{
	if(ms <= 0)
	{
		CLEM_ENGINE_CRITICAL("Set ms per render non positive");
		assert(false);
	}
	msPerRender = ms;
}

/**
 * @brief 获取实时FPS.
 * 
 * @return short .
 */
short Director::getFramesPerSecond() const
{
	return framesPerSecond;
}

/**
 * @brief 主循环.
 */
void Director::loop()
{
	CLEM_ENGINE_INFO("Main loop started");
	PROFILE_SESSION_BEGIN();

	long previous = getCurrentMillSecond();

	while(running)
	{
		PROFILE_FUNC();

		long current = getCurrentMillSecond();
		long dt      = current - previous;
		previous     = current;

		update(dt);
		render(dt);

		if(paused)
		{
			while(paused)
				sleep_for(milliseconds(500));
			previous = getCurrentMillSecond();
		}
	}

	PROFILE_SESSION_END();
	CLEM_ENGINE_INFO("Main loop stoped");
}

/**
 * @brief 更新场景.
 * 
 * @param dt .
 */
void Director::update(long dt)
{
	auto scene = scenes.back();

	static long updateLag = 0;
	updateLag += dt;
	while(updateLag >= msPerUpdate)
	{
		PROFILE_FUNC();

		scene->update((float)msPerUpdate / 1000);
		updateLag -= msPerUpdate;
	}
}

#include "terminal.h"

/**
 * @brief 渲染场景.
 * 
 * @param dt .
 */
void Director::render(long dt)
{
	auto scene = scenes.back();

	static long fpsLag = 0, frames = 0;
	const long  target = 1000 / msPerRender;
	fpsLag += dt;
	if(fpsLag >= 1000)
	{
		framesPerSecond = frames;
		frames = fpsLag = 0;
		Terminal::setTitle("Clementine | Render: " + std::to_string(getFramesPerSecond()) + "(" + std::to_string(target) + ")" + "FPS");
	}

	static long renderLag = 0;
	renderLag += dt;
	if(renderLag >= msPerRender)
	{
		PROFILE_FUNC();

		scene->render();
		renderLag = 0;
		frames++;
	}
}

#ifdef OS_UNIX

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

Director::Director()
		: running(false), paused(false), msPerUpdate(16), msPerRender(16), framesPerSecond(0)
{
	Log::init();

	// 开启 raw 模式
	termios mode;
	if(tcgetattr(STDOUT_FILENO, &mode) == -1)
		assert(false);
	mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	mode.c_cflag |= (CS8);
	mode.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	mode.c_cc[VMIN]  = 0;
	mode.c_cc[VTIME] = 0;
	if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &mode) == -1)
		assert(false);
}

/**
 * @brief 获取终端缓冲区大小.
 */
Size Director::getWinSize() const
{
	winsize winSize;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &winSize);
	return Size(winSize.ws_col, winSize.ws_row + 1);
}

#include <sys/time.h>

/**
 * @brief 获取当前毫秒数.
 * 
 * @return long 当前毫秒数.
 */
long Director::getCurrentMillSecond() const
{
	PROFILE_FUNC();

	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec * 0.001;
}

#endif // OS_UNIX

#ifdef OS_WIN

Director::Director()
		: running(false), paused(false), msPerUpdate(16), msPerRender(16), framesPerSecond(0)
{
	Log::init();

	// 开启 VT100 模式
	const auto hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD      mode;
	if(!GetConsoleMode(hStdOut, &mode))
		assert(false);
	if(!SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		assert(false);
}

/**
 * @brief 获取终端缓冲区大小
 * 
 * @return Size 终端缓冲区大小
 */
Size Director::getWinSize() const
{
	static const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	auto                       ret = GetConsoleScreenBufferInfo(hOut, &screenInfo);
	if(!ret)
		assert(false);

	return Size(screenInfo.srWindow.Right + 1, screenInfo.srWindow.Bottom + 1);
}

long Director::getCurrentMillSecond() const
{
	PROFILE_FUNC();

	LARGE_INTEGER freq;
	BOOL          ret = QueryPerformanceFrequency(&freq);
	assert(ret != 0);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time.QuadPart * 1000 / freq.QuadPart;
}

#endif // OS_WIN
