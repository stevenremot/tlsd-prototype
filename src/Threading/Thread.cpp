#include "Thread.h"

#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

using std::vector;

namespace Threading {

    int sleep(long seconds, long milliseconds)
    {
        struct timespec tim;
        tim.tv_sec = seconds;
        tim.tv_nsec = milliseconds * 1000000L;
        //return nanosleep(&tim, NULL);
        return 0;
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
    }

    void* Thread::loopFunction(void * obj)
    {
        Thread * thread = static_cast<Thread*>(obj);
        vector<ThreadableInterface*> threadables = thread->threadables_;
        unsigned int threadablesSize = threadables.size();

        time_t lastTime = std::time(NULL);
        time_t delay = 0;
        time_t currentTime;
        time_t loopDelay = thread->loopDelay_;

        while (thread->isRunning())
        {
            currentTime = std::time(NULL);
            delay += (currentTime - lastTime) * 1000;
            lastTime = currentTime;

            while (delay >= loopDelay)
            {
                for (unsigned int i = 0; i < threadablesSize; i++)
                {
                    threadables[i]->run();
                }
                delay -= loopDelay;
            }

            Threading::sleep(0, static_cast<long>(loopDelay - delay));
        }

        return NULL;
    }
}
