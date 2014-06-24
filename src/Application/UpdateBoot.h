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

#ifndef APPLICATION_UPDATE_BOOT_H
#define APPLICATION_UPDATE_BOOT_H

#include "BootInterface.h"

#include "../Physics/MovementSystem.h"
#include "../Physics/CollisionSystem.h"

namespace Application
{
    class UpdateBoot: public BootInterface
    {
    public:
        UpdateBoot(Callback callback, Application& application):
            BootInterface(callback, application),
            movementSystem_(NULL),
            collisionSystem_(NULL)
        {}

        virtual void start();

    protected:

        virtual void cleanUp()
        {
            if (movementSystem_ != NULL)
            {
                delete collisionSystem_;
                delete movementSystem_;
            }
        }

    private:
        Physics::MovementSystem* movementSystem_;
        Physics::CollisionSystem* collisionSystem_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
