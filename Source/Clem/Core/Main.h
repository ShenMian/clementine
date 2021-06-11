// Copyright 2021 SMS
// License(Apache-2.0)

#pragma once

int main(int argc, char* argv[]);

namespace clem
{

/**
 * @addtogroup Core
 * @{
 */

class Main
{
public:
    Main(int argc, char* argv[]);
    ~Main();

    void run();
    void stop();

    uint16_t getFrameRate() const;

private:
    void init();
    void deinit();

private:
  void mainLoop();
	void parseArgs(int argc, char* argv[]);
};

/**
 * end of Core group
 * @}
 */

} // namespace clem
