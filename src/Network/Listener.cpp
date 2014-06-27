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
#include "Listener.h"

using std::cout;
using std::endl;

namespace Network
{
    Listener::Listener(vector<string>* ListeEvent, TCPSocket* client)
    {
        this->ListeEvent_=ListeEvent;
        this->client_=client;
    }

    Listener::~Listener()
    {
        this->ListeEvent_=NULL;
        this->client_=NULL;
    }

    void Listener::run(void)
    {
        if(this->client_!=NULL )
        {
            try{
                char* buffer = new char[2000];
                int recvMsgSize = client_->recv(buffer, 2000);

                while (recvMsgSize > 0)   // Zero means
                {
                    cout<<"Message recu "<<buffer<<endl;
                    recvMsgSize = client_->recv(buffer, 2000);
                }

                delete[] buffer;
            }catch(const SocketException& e)
            {
                cerr <<" Socket exception : " << e.what() <<  endl;
            }
        }

    }
}
