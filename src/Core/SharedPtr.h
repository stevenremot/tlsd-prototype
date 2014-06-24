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

#ifndef CORE_SHARED_PTR_H_H
#define CORE_SHARED_PTR_H_H

#include <cstdlib>
#include <exception>

#include "../Threading/Lock.h"

namespace Core
{
    template <typename T>
    class SharedPtr;

    template<typename T1, typename T2>
    SharedPtr<T2> castSharedPtr(const SharedPtr<T1> ptr);

    /**
     * A class of pointer shared between different objets
     *
     * None of the objects handle pointer's memory. It handles it by itself
     * using a reference counting startegy.
     *
     * TODO : be more careful about memory corruption ?
     */
    template<typename T>
    class SharedPtr
    {
    public:
        SharedPtr(T* data):
            data_(data),
            refs_(new unsigned int),
            lock_(new Threading::Lock())
        {
            *refs_ = 1;
        }

        SharedPtr(const SharedPtr& ptr):
            data_(ptr.data_),
            refs_(ptr.refs_),
            lock_(ptr.lock_)
        {
            lock_->lockForWriting();
            (*refs_) += 1;
            lock_->unlockForWriting();
        }

        SharedPtr& operator=(const T* data)
        {
            unassign();
            data_ = data;
            refs_ = new unsigned int;
            lock_ = new Threading::Lock();
            *refs_ = 1;

            return *this;
        }

        SharedPtr& operator=(const SharedPtr& ptr)
        {
            unassign();
            data_ = ptr.data_;
            refs_ = ptr.refs_;
            lock_ = ptr.lock_;
            lock_->lockForWriting();
            (*refs_) += 1;
            lock_->unlockForWriting();

            return *this;
        }

        ~SharedPtr()
        {
            unassign();
        }

        T& operator*()
        {
            return *data_;
        }

        T* operator->()
        {
            return data_;
        }

        template<typename T1, typename T2>
        friend SharedPtr<T2> castSharedPtr(const SharedPtr<T1> ptr);

    private:
        T* data_;
        unsigned int* refs_;
        Threading::Lock* lock_;

        void unassign()
        {
            lock_->lockForWriting();
            (*refs_) -= 1;

            if (*refs_ == 0)
            {
                lock_->unlockForWriting();
                delete data_;
                delete refs_;
                delete lock_;
                data_ = NULL;
                refs_ = NULL;
                lock_ = NULL;
            }
            else
            {
                lock_->unlockForWriting();
            }
        }

        SharedPtr(unsigned int* refs, T* data, Threading::Lock* lock):
            data_(data),
            refs_(refs),
            lock_(lock)
        {
            lock_->lockForWriting();
            (*refs) += 1;
            lock_->unlockForWriting();
        }
    };

    template<typename T1, typename T2>
    SharedPtr<T2> castSharedPtr(const SharedPtr<T1> ptr)
    {
        return SharedPtr<T2>(ptr.refs_, static_cast<T2*>(ptr.data_), ptr.lock_);
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
