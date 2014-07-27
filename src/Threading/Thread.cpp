#include "Thread.h"

#include "../Core/Time.h"

using std::vector;

using Core::getTime;
using Core::difference;

namespace Threading
{
    void sleep(const Core::Duration& duration)
    {
        std::this_thread::sleep_for(duration);
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

        Core::TimePoint lastTime = Core::getTime();

        Core::Duration delay = Core::makeDurationMillis(0);
        Core::Duration loopDelay = Core::makeDurationMillis(loopDelay_);

        while (isRunning())
        {
            Core::TimePoint currentTime = getTime();
            delay += difference(lastTime, currentTime);
            lastTime = currentTime;

            while (delay >= loopDelay && isRunning())
            {
                for (unsigned int i = 0; i < threadablesSize; i++)
                {
                    threadables_[i]->run();
                }
                delay -= loopDelay;
            }

            Threading::sleep(loopDelay - delay);
        }
    }
}
