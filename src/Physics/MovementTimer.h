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

#ifndef PHYSICS_MOVEMENTTIMER_H
#define PHYSICS_MOVEMENTTIMER_H

#include "../Core/Time.h"

namespace Physics
{
    class MovementTimer
    {
    public:
        MovementTimer():
            lastTime_(),
            currentTime_(),
            delay_(Core::makeDurationMillis(0))
        {}

        void updateCurrentTime();
        void updateLastTime();

        unsigned long getLastTime() const;
        unsigned long getDelay() const;

    private:
        Core::TimePoint lastTime_, currentTime_;
        Core::Duration delay_;
    };
}

#endif // PHYSICS_MOVEMENTTIMER_H
