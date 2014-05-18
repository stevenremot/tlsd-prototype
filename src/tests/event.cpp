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

#include "event.h"

#include <iostream>
#include <vector>

#include "../Event/EventManager.h"
#include "../Threading/Thread.h"

using std::cout;
using std::endl;
using std::vector;

namespace EventTest
{

    const Event::Event::Type QuitEvent::TYPE = "quit";
    const Event::Event::Type PrintEvent::TYPE = "print";

    void PrintListener::call(const Event::Event & event)
    {
        cout << static_cast<const PrintEvent &>(event).getChar();
    }

    static bool loop = true;

    void QuitListener::call(const Event::Event & event)
    {
        loop = false;
    }

    void testEvents()
    {
        Event::EventManager m;
        Event::ListenerRegister & reg = m.getListenerRegister();

        reg.put(PrintEvent::TYPE, new PrintListener());
        reg.put(QuitEvent::TYPE, new QuitListener());

        vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(&m);

        Threading::Thread eventThread(threadables, 3);
        eventThread.start();

        Event::EventQueue & queue = m.getEventQueue();

        queue << new PrintEvent('h');
        queue << new PrintEvent('e');
        queue << new PrintEvent('l');
        queue << new PrintEvent('l');
        queue << new PrintEvent('o');
        queue << new QuitEvent();

        while (loop)
        {
            cout << ".";
            Threading::sleep(0, 200);
        }

        eventThread.stop();
    }
}
