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

#ifndef THREADING_LOCK_H
#define THREADING_LOCK_H

#include "Thread.h"

namespace Threading
{
    /**
     * Basic class for locking data for read / write
     */
    class Lock
    {
    public:
        Lock():
            hasWriter_(false),
            readers_(0)
        {}

        void lockForReading()
        {
            while (hasWriter_)
            {
                Threading::sleep(0, 50);
            }
            readers_ += 1;
        }

        void unlockForReading()
        {
            readers_ -= 1;
        }

        void lockForWriting()
        {
            while (readers_ > 0 && hasWriter_)
            {
                Threading::sleep(0, 50);
            }

            hasWriter_ = true;
        }

        void unlockForWriting()
        {
            hasWriter_ = false;
        }

    private:
        bool hasWriter_;
        unsigned int readers_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
