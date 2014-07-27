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

#ifndef CORE_TIME_H
#define CORE_TIME_H

#include <chrono>

namespace Core
{
    typedef std::chrono::steady_clock::time_point TimePoint;
    typedef std::chrono::milliseconds Duration;

    /**
     * Return the time point since an arbitrary and constant start
     *
     * @return Current time point
     */
    TimePoint getTime();

    /**
     *  Difference of time points : end - start
     */
    Duration difference(const TimePoint& start, const TimePoint& end);

    /**
     * Return a duration for milliseconds
     */
    Duration makeDurationMillis(unsigned long milliSeconds);

    /**
     * Return the milliseconds of the duration
     */
    unsigned long getDurationMillis(const Duration& duration);
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
