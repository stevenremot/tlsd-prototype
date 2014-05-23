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

#include "core.h"

#include <iostream>

#include "../Core/SharedPtr.h"

using std::cout;
using std::endl;

using Core::SharedPtr;

namespace CoreTest
{
    class SharedData
    {
    public:
        static unsigned int getRefs()
        {
            return refs_;
        }

        SharedData()
        {
            refs_ += 1;
        }

        ~SharedData()
        {
            refs_ -= 1;
        }

    private:
        static unsigned int refs_;
    };

    unsigned int SharedData::refs_ = 0;

    void testSharedPtr()
    {
        bool failed = false;

        if (SharedData::getRefs() != 0)
        {
            cout << "SharedPtr : wtf ?!" << endl;
            failed = true;
        }

        {
            SharedPtr<SharedData> basePtr(new SharedData());

            if (SharedData::getRefs() != 1)
            {
                cout << "SharedPtr : wrong reference, should be 1, is "
                     << SharedData::getRefs() << endl;
                failed = true;
            }

            {
                SharedPtr<SharedData> secondPtr = basePtr;


                if (SharedData::getRefs() != 1)
                {
                    cout << "SharedPtr : wrong reference, should still be 1, is "
                         << SharedData::getRefs() << endl;
                    failed = true;
                }
            }

            if (SharedData::getRefs() != 1)
            {
                cout << "SharedPtr : wrong reference, should be 1 again, is "
                     << SharedData::getRefs() << endl;
                failed = true;
            }
        }

        if (SharedData::getRefs() != 0)
        {
            cout << "SharedPtr : wrong reference, should be 0, is "
                 << SharedData::getRefs() << endl;
            failed = true;
        }

        if (!failed)
        {
            cout << "SharedPtr : all tests passed." << endl;
        }
    }
}
