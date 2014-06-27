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
namespace Network
{
    AcceptClient::AcceptClient(TCPServerSocket *Server,vector<TCPSocket*> *ListeClient)
    {
        this->Server_=Server;
        this->ListeClient_=ListeClient;
    }

    AcceptClient::~AcceptClient()
    {
        this->Server_=NULL;
        this->ListeClient_=NULL;
    }

    void AcceptClient::run(void)
    {

        TCPSocket *clntSock= this->Server_->accept();
        // Create separate memory for client argument

        if(clntSock != NULL)
        {
            /// Ajouter des sémaphores
            this->ListeClient_->push_back(clntSock);
            std::cout<<"Client accepte"<<std::endl;
            Listener* listener=new Listener(NULL, ListeClient_->back());
            std::vector<ThreadableInterface*> threadables;

            threadables.push_back(listener);

            this->thread_=new Thread(threadables, 2);
            this->thread_->start();
        }
        else
        {
            /// A supprimer
            std::cout<<" Erreur pour accepter client"<<std::endl;
        }
    }
}
