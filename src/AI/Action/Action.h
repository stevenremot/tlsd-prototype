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

#ifndef AI_ACTION_ACTION_H
#define AI_ACTION_ACTION_H

#include <string>

namespace AI
{
    namespace Action
    {
        /**
         * Base class for actions. Overload it to define custom actions.
         */
        class Action
        {
        public:

            typedef std::string ActionType;

            Action(const ActionType& type) : type_(type){}

            const ActionType& getType() const {return type_;}

            bool isFinished() const {return finished_;}
            void setFinished(bool finished) {finished_ = finished;}

        private:
            ActionType type_;
            bool finished_;
        };
    }
}

#endif // AI_ACTION_ACTION_H
