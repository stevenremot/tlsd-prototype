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

#ifndef THREADING_CONCURRENT_RESSOURCE_H
#define THREADING_CONCURRENT_RESSOURCE_H

#include "Lock.h"

namespace Threading
{

    template<typename T>
    class ConcurrentReader
    {
    public:
        ConcurrentReader(Lock& lock, const T& data):
            lock_(lock),
            data_(data)
        {
            lock.lockForReading();
        }

        ~ConcurrentReader()
        {
            lock_.unlockForReading();
        }

        const T& operator*()
        {
            return data_;
        }

        const T& operator->()
        {
            return data_;
        }

    private:
        Lock& lock_;
        const T& data_;
    };

    template<typename T>
    class ConcurrentWriter
    {
    public:
        ConcurrentWriter(Lock& lock, T& data):
            lock_(lock),
            data_(data)
        {
            lock.lockForWriting();
        }

        ~ConcurrentWriter()
        {
            lock_.unlockForWriting();
        }

        T& operator*()
        {
            return data_;
        }

        T& operator->()
        {
            return data_;
        }

    private:
        Lock& lock_;
        T& data_;
    };

    /**
     * Class for handling data with concurrent accesses.
     */
    template<typename T>
    class ConcurrentRessource
    {
    public:
        ConcurrentRessource(T* data):
            data_(data)
        {}

        ~ConcurrentRessource()
        {
            delete data_;
        }

        ConcurrentReader<T> getReader()
        {
            return ConcurrentReader<T>(lock_, data_);
        }

        ConcurrentWriter<T> getWriter()
        {
            return ConcurrentWriter<T>(lock_, data_);
        }

    private:
        Lock lock_;
        T* data_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
