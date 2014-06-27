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

#include <sstream>

#include "EventDeserialization.h"

using std::cout;
using std::endl;

namespace Network
{
    Listener::Listener(
        TCPSocket* client,
        Event::EventQueue& eventQueue,
        ConnectionClosedCallbackInterface* conCloseCallback
    ): client_(client),
       eventQueue_(eventQueue),
       conCloseCallback_(conCloseCallback)
    {}

    Listener::~Listener()
    {
        delete conCloseCallback_;
    }

    void Listener::run(void)
    {
        if(this->client_!=NULL )
        {
            std::string message;
            char* buffer = new char[2000];

            int recvMsgSize = 0;

            try
            {
                recvMsgSize = client_->recv(buffer, 2000);

            }
            catch(const SocketException& e)
            {
                cerr <<" Socket exception : " << e.what() <<  endl;
                delete[] buffer;
                conCloseCallback_->onClose();
                return;
            }

            if (recvMsgSize > 0)
            {
                message += buffer;
                handleMessage(message);
            }
            else if (recvMsgSize < 0)
            {
                cout << "Connection closed ?" << endl; // TODO remove
                conCloseCallback_->onClose();
            }

            delete[] buffer;
        }

    }


    void Listener::handleMessage(const std::string& msg)
    {
        std::stringstream sstream(msg);
        string type;
        sstream >> type;

        if (type == "event")
        {
            eventQueue_ << deserializeEvent(sstream);
        }
    }
}
