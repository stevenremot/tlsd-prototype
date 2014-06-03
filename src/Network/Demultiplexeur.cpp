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
Demultiplexeur::Demultiplexeur(std::vector<TCPSocket*>* ListeClient,std::vector<string>* ListeEvent,TCPServerSocket* ServerSocket)
{
    //ctor
    this->ListeClient_=ListeClient;
    this->ListeEvent_=ListeEvent;
    this->ServerSocket_=ServerSocket;
}

Demultiplexeur::~Demultiplexeur()
{
    this->ListeClient_=NULL;
    this->ListeEvent_=NULL;
}

void Demultiplexeur::run(void)
{
    if(this->ListeClient_!=NULL && this->ListeEvent_!=NULL && this->ListeEvent_->size()!=0)
    {
        for(int i=0; i < ListeClient_->size(); i++)
        {
            SendEvent((*ListeClient_)[i],(ListeEvent_->front()));
        }
                    ListeEvent_->erase(ListeEvent_->begin());
    }
}
}
