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

#ifndef LISTENER_H
#define LISTENER_H
#include <vector>
#include <iostream>

#include "PracticalSocket.h"
#include "../Threading/Thread.h"
#include "../Event/EventQueue.h"

namespace Network{
    class Listener : public Threading::ThreadableInterface
    {
    public:
        Listener(
            std::vector<string>* ListeEvent,
            TCPSocket* client,
            Event::EventQueue& eventQueue
        );
        virtual ~Listener();
        void run(void);

    private:
        std::vector<string>* ListeEvent_;
        TCPSocket* client_;
        Event::EventQueue& eventQueue_;

        void handleMessage(const std::string& msg);
    };
}
#endif // LISTENER_H
