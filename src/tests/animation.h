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

#ifndef TESTS_ANIMATION_H
#define TESTS_ANIMATION_H

#include "../Event/Event.h"
#include "../Event/EventListenerInterface.h"
#include "../Event/EventManager.h"

namespace AnimationTest
{
    class DummyInputListener: public Event::EventListenerInterface
    {
    public:
        DummyInputListener(Event::EventQueue& eventQueue):
            eventQueue_(eventQueue)
            {}

        virtual void call(const Event::Event & event);

    private:
        Event::EventQueue& eventQueue_;
    };

    void testAnimation();
};

#endif // TESTS_ANIMATION_H
