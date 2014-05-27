#include "Thread.h"

#include <iostream>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

using std::cout;
using std::endl;

using std::vector;

namespace Threading
{

#ifdef _WIN32
    int win_gettime(struct timespec* time)
    {
        SYSTEMTIME st;
        GetSystemTime(&st);

        time->tv_sec = st.wSecond;
        time->tv_nsec = st.wMilliseconds * 1000000L;

        return 0;
    }

#endif // _WIN32


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

    // end - start
    struct timespec difference(struct timespec start, struct timespec end)
    {
        struct timespec temp;
        if (end.tv_nsec-start.tv_nsec < 0)
        {
            temp.tv_sec = end.tv_sec - start.tv_sec-1;
            temp.tv_nsec = 1000000000L + end.tv_nsec-start.tv_nsec;
        }
        else
        {
            temp.tv_sec = end.tv_sec - start.tv_sec;
            temp.tv_nsec = end.tv_nsec - start.tv_nsec;
        }
        return temp;
    }

    void Thread::start()
    {
        running_ = true;
        int ret = pthread_create(&thread_, NULL, Thread::loopFunction, this);

        if (ret)
        {
            throw Exception(ret);
        }
    }

    void Thread::stop()
    {
        running_ = false;
        pthread_join(thread_, NULL);
    }

    void* Thread::loopFunction(void * obj)
    {
        Thread * thread = static_cast<Thread*>(obj);
        vector<ThreadableInterface*> threadables = thread->threadables_;
        unsigned int threadablesSize = threadables.size();

        struct timespec lastTime;
#ifdef _WIN32
        win_gettime(&lastTime);
#else
        clock_gettime(CLOCK_MONOTONIC, &lastTime);
#endif // _WIN32
        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = 0;
        struct timespec currentTime;
        struct timespec loopDelay;
        loopDelay.tv_sec = 0;
        loopDelay.tv_nsec = 1000000L * thread->loopDelay_;

        while (thread->isRunning())
        {
#ifdef _WIN32
            win_gettime(&currentTime);
#else
            clock_gettime(CLOCK_MONOTONIC, &currentTime);
#endif // _WIN32
            struct timespec diff = difference(lastTime, currentTime);
            delay.tv_sec += diff.tv_sec;
            delay.tv_nsec += diff.tv_nsec;
            lastTime = currentTime;

            struct timespec diffDelays = difference(loopDelay, delay);
            while (diffDelays.tv_sec >= 0 && diffDelays.tv_nsec >= 1000)
            {
                for (unsigned int i = 0; i < threadablesSize; i++)
                {
                    threadables[i]->run();
                }
                delay = diffDelays;
                diffDelays = difference(loopDelay, delay);
            }

            //int ret = Threading::sleep(0, static_cast<long>(loopDelay.tv_sec - delay.tv_sec));
            struct timespec waitingTime = difference(delay, loopDelay);
            Threading::sleep(waitingTime.tv_sec, waitingTime.tv_nsec / 1000000L);
        }

        return NULL;
    }
}
