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

#include "AcceptClient.h"
#include "ServerConnectionClosedCallback.h"

#include "Server.h"

namespace Network
{
    AcceptClient::AcceptClient(
        Server &Server,
        Threading::ConcurrentRessource< vector<TCPSocket*> >& ListeClient,
        std::vector<Threading::Thread*>& clientThreads,
        Event::EventQueue& queue
    ): Server_(Server),
       ListeClient_(ListeClient),
       clientThreads_(clientThreads),
       eventQueue_(queue)
    {}

    void AcceptClient::run(void)
    {
        TCPSocket *clntSock = Server_.getSocket().accept();
        // Create separate memory for client argument

        if(clntSock != NULL)
        {
            Threading::ConcurrentWriter< vector<TCPSocket*> > clientList =
                ListeClient_.getWriter();

            /// Ajouter des sémaphores
            clientList->push_back(clntSock);
            std::cout<<"Client accepte"<<std::endl;
            Listener* listener=new Listener(
                clientList->back(),
                eventQueue_,
                new ServerConnectionClosedCallback(Server_, clntSock)
            );
            std::vector<ThreadableInterface*> threadables;

            threadables.push_back(listener);

            Threading::Thread* thread = new Threading::Thread(threadables, 2);
            thread->start();
            clientThreads_.push_back(thread);
        }
        else
        {
            /// A supprimer
            std::cout<<" Erreur pour accepter client"<<std::endl;
        }
    }
}
