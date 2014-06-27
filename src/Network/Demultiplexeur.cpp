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

#include "Demultiplexeur.h"
namespace Network
{
    Demultiplexeur::Demultiplexeur(
        Threading::ConcurrentRessource< std::vector<TCPSocket*> >& ListeClient,
        std::vector<string>* ListeEvent
    ):  ListeClient_(ListeClient),
        ListeEvent_(ListeEvent)
    {}

    Demultiplexeur::~Demultiplexeur()
    {
    }

    void Demultiplexeur::run(void)
    {
        if(ListeEvent_ != NULL && ListeEvent_->size() != 0)
        {
            Threading::ConcurrentReader< std::vector<TCPSocket*> > clientList =
                ListeClient_.getReader();

            for(unsigned int i=0; i < clientList->size(); i++)
            {
                try
                {
                    SendEvent((*clientList)[i],(ListeEvent_->front()));
                }
                catch(const SocketException& e)
                {
                    cout << "Test" << endl; // TODO remove
                }
            }
            ListeEvent_->erase(ListeEvent_->begin());
        }
    }
}
