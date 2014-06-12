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

using Threading::ThreadableInterface;
using Threading::Thread;
namespace Network
{
class AcceptClient : public ThreadableInterface
{
public:
    AcceptClient(TCPServerSocket *Server,std::vector<TCPSocket*> *ListeClient);
    virtual ~AcceptClient();
    void run(void);
protected:
private:
    TCPServerSocket *Server_;
    vector<TCPSocket*> *ListeClient_;
    Thread* thread_;
};
}
#endif // ACCEPTCLIENT_H
