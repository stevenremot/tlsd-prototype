#include "Thread.h"

#include <iostream>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../Core/Time.h"

using std::cout;
using std::endl;

using std::vector;

using Core::getTime;
using Core::difference;

namespace Threading
{
    int sleep(long seconds, long milliseconds)
    {
#ifdef _WIN32
        Sleep(seconds * 1000L + milliseconds);
        return 0;
#else
        struct timespec tim;
        tim.tv_sec = seconds;
        tim.tv_nsec = milliseconds * 1000000L;
        return nanosleep(&tim, NULL);
#endif
    }

    void Thread::start()
    {
        running_ = true;
        thread_ = std::thread([this](){ this->loopFunction(); });
    }

    void Thread::stop()
    {
        running_ = false;
        thread_.join();
    }

    void Thread::loopFunction()
    {
        unsigned int threadablesSize = threadables_.size();

        struct timespec lastTime;
        getTime(lastTime);

        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = 0;
        struct timespec currentTime;
        struct timespec loopDelay;
        loopDelay.tv_sec = 0;
        loopDelay.tv_nsec = 1000000L * loopDelay_;

        while (isRunning())
        {
            getTime(currentTime);
            struct timespec diff = difference(lastTime, currentTime);
            delay.tv_sec += diff.tv_sec;
            delay.tv_nsec += diff.tv_nsec;
            lastTime = currentTime;

            struct timespec diffDelays = difference(loopDelay, delay);
            while (diffDelays.tv_sec >= 0 && diffDelays.tv_nsec >= 1000 && isRunning())
            {
                for (unsigned int i = 0; i < threadablesSize; i++)
                {
                    threadables_[i]->run();
                }
                delay = diffDelays;
                diffDelays = difference(loopDelay, delay);
            }

            struct timespec waitingTime = difference(delay, loopDelay);
            Threading::sleep(waitingTime.tv_sec, waitingTime.tv_nsec / 1000000L);
        }
    }
}
