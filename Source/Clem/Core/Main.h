#pragma once

#include <cstdint>

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

    void mainLoop();

    long getCurrentMillSecond() const;

    bool     quit      = true;
    uint16_t frameRate = 0;
};

