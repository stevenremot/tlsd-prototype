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

#ifndef TESTS_EVENT_H
#define TESTS_EVENT_H

#include "../Event/Event.h"
#include "../Event/EventListenerInterface.h"

namespace EventTest
{
    class QuitEvent: public Event::Event
    {
    public:
        static const Event::Type TYPE;
    QuitEvent(): Event::Event(TYPE)
        {}
    };

    class PrintEvent: public Event::Event
    {
    public:
        static const Type TYPE;

    PrintEvent(char c): Event::Event(TYPE), c_(c)
        {}

        char getChar() const
        {
            return c_;
        }

    private:
        char c_;
    };

    class PrintListener: public Event::EventListenerInterface
    {
    public:
        virtual void call(const Event::Event & event);
    };

    class QuitListener: public Event::EventListenerInterface
    {
    public:
        virtual void call(const Event::Event & event);
    };

    void testEvents();
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
