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

#include "Time.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace Core
{
    int getTime(struct timespec& time)
    {
#ifdef _WIN32
        SYSTEMTIME st;
        GetSystemTime(&st);

        time.tv_sec = st.wSecond;
        time.tv_nsec = st.wMilliseconds * 1000000L;

        return 0;
#else
        return clock_gettime(CLOCK_MONOTONIC, &time);
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
}
