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

#ifndef EVENT_EVENT_H
#define EVENT_EVENT_H

#include <string>

namespace Event {
    /**
     * Base class for all the application's events.
     */
    class Event {
    public:
        /**
         * The type of event's types.
         *
         * Each event should define it's type as a static variable named Type,
         * and pass it in Event base constructor at instanciation.
         */
        typedef std::string Type;

        Event(const Type & type): type_(type)
        {}

        Event (const Event & event): type_(event.type_)
        {}

        virtual ~Event()
        {}

        /**
         * Convert the event to a string.
         *
         * It allows Event sending over the network.
         *
         * TODO: Externalize?
         */
        virtual std::string serialize() const = 0;

        const Type & getType() const
        {
            return type_;
        }

    private:
        Type type_;
    };

}
#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
