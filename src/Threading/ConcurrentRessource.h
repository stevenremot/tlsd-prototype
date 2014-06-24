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
#include "../Core/SharedPtr.h"

namespace Threading
{
    template<typename T>
    class ConcurrentRessource;

    template<typename T>
    class ConcurrentReader;

    template<typename T>
    class ConcurrentWriter;

    template <typename T1, typename T2>
    ConcurrentReader<T2> getConcurrentReader(ConcurrentRessource<T1> res);

    template <typename T1, typename T2>
    ConcurrentWriter<T2> getConcurrentWriter(ConcurrentRessource<T1> res);

    template<typename T>
    class ConcurrentReader
    {
    public:
        ConcurrentReader(const Core::SharedPtr<Lock>& lock, const Core::SharedPtr<T>& data):
            lock_(lock),
            data_(data)
        {
            lock_->lockForReading();
        }

        ~ConcurrentReader()
        {
            lock_->unlockForReading();
        }

        const T& operator*()
        {
            return *data_;
        }

        const T* operator->()
        {
            return &*data_;
        }

    private:
        Core::SharedPtr<Lock> lock_;
        Core::SharedPtr<T> data_;
    };

    template<typename T>
    class ConcurrentWriter
    {
    public:
        ConcurrentWriter(const Core::SharedPtr<Lock>& lock, const Core::SharedPtr<T>& data):
            lock_(lock),
            data_(data)
        {
            lock_->lockForWriting();
        }

        ~ConcurrentWriter()
        {
            lock_->unlockForWriting();
        }

        T& operator*()
        {
            return *data_;
        }

        T* operator->()
        {
            return &*data_;
        }

    private:
        Core::SharedPtr<Lock> lock_;
        Core::SharedPtr<T> data_;
    };

    /**
     * Class for handling data with concurrent accesses.
     */
    template<typename T>
    class ConcurrentRessource
    {
    public:
        ConcurrentRessource(T* data):
            lock_(new Lock()),
            data_(data)
        {}

        ConcurrentRessource(const ConcurrentRessource& res):
            lock_(res.lock_),
            data_(res.data_)
        {}

        ConcurrentReader<T> getReader()
        {
            return ConcurrentReader<T>(lock_, data_);
        }

        ConcurrentWriter<T> getWriter()
        {
            return ConcurrentWriter<T>(lock_, data_);
        }

        template<typename U, typename V>
        friend ConcurrentReader<V> getConcurrentReader(ConcurrentRessource<U>);

        template<typename U, typename V>
        friend ConcurrentWriter<V> getConcurrentWriter(ConcurrentRessource<U>);

    private:
        Core::SharedPtr<Lock> lock_;
        Core::SharedPtr<T> data_;
    };

    template <typename T1, typename T2>
    ConcurrentReader<T2> getConcurrentReader(ConcurrentRessource<T1> res)
    {
        return ConcurrentReader<T2>(
            res.lock_,
            Core::castSharedPtr<T1, T2>(res.data_)
        );
    }


    template <typename T1, typename T2>
    ConcurrentWriter<T2> getConcurrentWriter(ConcurrentRessource<T1> res)
    {
        return ConcurrentWriter<T2>(
            res.lock_,
            Core::castSharedPtr<T1, T2>(res.data_)
        );
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
