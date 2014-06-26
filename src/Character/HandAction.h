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

#ifndef CHARACTER_HAND_ACTION_H
#define CHARACTER_HAND_ACTION_H

#include "Action.h"

namespace Character
{
    enum Hand { LeftHand, RightHand };

    class StartHandAction: public Action
    {
    public:
        static const Type Type;

        StartHandAction(const Hand& hand):
            Action(Type),
            hand_(hand)
        {}

        const Hand& getHand() const
        {
            return hand_;
        }

    private:
        Hand hand_;
    };

    class StopHandAction: public Action
    {
    public:
        static const Type Type;

        StopHandAction(const Hand& hand):
            Action(Type),
            hand_(hand)
        {}

        const Hand& getHand() const
        {
            return hand_;
        }

    private:
        Hand hand_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
