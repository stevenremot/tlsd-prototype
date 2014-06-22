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

#include <exception>

namespace Core
{
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
            refs_(new unsigned int)
        {
            *refs_ = 1;
        }

        SharedPtr(const SharedPtr& ptr):
            data_(ptr.data_),
            refs_(ptr.refs_)
        {
            (*refs_) += 1;
        }

        SharedPtr& operator=(const T* data)
        {
            unassign();
            data_ = data;
            refs_ = new unsigned int;
            *refs_ = 1;

            return *this;
        }

        SharedPtr& operator=(const SharedPtr& ptr)
        {
            unassign();
            data_ = ptr.data_;
            refs_ = ptr.refs_;
            (*refs_) += 1;

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

    private:
        T* data_;
        unsigned int* refs_;

        void unassign()
        {
            (*refs_) -= 1;

            if (*refs_ == 0 && refs_ != NULL)
            {
                delete data_;
                delete refs_;
                data_ = NULL;
                refs_ = NULL;
            }
        }
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
