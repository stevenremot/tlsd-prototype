#include "MovementTimer.h"
#include "../Threading/Thread.h"

namespace Physics
{
    void MovementTimer::updateCurrentTime()
    {
        struct timespec time;
        Threading::getTime(time);
        currentTime_ = time.tv_sec * 1000L + time.tv_nsec / 1000000L;
        delay_ = currentTime_ - lastTime_;
    }

    void MovementTimer::updateLastTime()
    {
        lastTime_ = currentTime_;
    }

    unsigned long MovementTimer::getLastTime() const
    {
        return lastTime_;
    }

    unsigned long MovementTimer::getDelay() const
    {
        return delay_;
    }
}
