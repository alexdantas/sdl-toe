#ifndef TIMER_H_DEFINED
#define TIMER_H_DEFINED

#include <string>
#include <sstream>
#include "SDLManager.hpp"

class Timer
{
public:
    Timer();

    /// Sets a starting point for the timer.
    void start();

    /// Sets a stopping point for the timer.
    void stop();

    /// Tells if the timer's still running (hasn't called stop())
    bool isRunning();

    /// Returns the timer's difference in milisseconds.
    //  @note If the timer's not started, will return 0.
    Uint32 delta_ms();

    /// Returns the difference between timer's start point and now.
    Uint32 currentTime();

private:
    Uint32 startMark;
    Uint32 stopMark;
    bool   running;
};

#endif /* TIMER_H_DEFINED */
