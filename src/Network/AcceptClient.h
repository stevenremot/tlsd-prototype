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
#ifndef ACCEPTCLIENT_H
#define ACCEPTCLIENT_H

#include "PracticalSocket.h"
#include <vector>
#include <iostream>
#include "Listener.h"
#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
#include "../Event/EventQueue.h"

namespace Network
{
    class Server;

    class AcceptClient : public Threading::ThreadableInterface
    {
    public:
        AcceptClient(
            Server &Server,
            Threading::ConcurrentRessource< std::vector<TCPSocket*> >& ListeClient,
            std::vector<Threading::Thread*>& clientThreads,
            Event::EventQueue& queue
        );

        void run(void);

    protected:
    private:
        Server& Server_;
        Threading::ConcurrentRessource< vector<TCPSocket*> > ListeClient_;
        std::vector<Threading::Thread*>& clientThreads_;
        Event::EventQueue& eventQueue_;
    };
}
#endif // ACCEPTCLIENT_H
