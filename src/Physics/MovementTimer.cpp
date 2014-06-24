/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

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
