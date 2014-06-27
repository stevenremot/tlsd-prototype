#ifndef CLIENT_H
#define CLIENT_H
#include "PracticalSocket.h"
#include <pthread.h>
#include <iostream>
#include "Listener.h"

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
#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
#include "../Event/EventQueue.h"
#include "Demultiplexeur.h"
using Threading::ThreadableInterface;

typedef string Port;
typedef string Ip;
typedef string Event2;
typedef int Serializer;
typedef int Deserializer;

namespace Network{
class Client
{
public:
    Client(Ip ip, string port, Event::EventQueue& eventqueue);
    virtual ~Client();
    void SetSerializer(Serializer *serializer);
    Serializer *GetSerializer();
    void SetDeserializer(Deserializer *deserializer );
    Deserializer *GetDeserializer();
    void SendEvent(Event2 event);

protected:
private:
    bool connected_;
    Listener* listener_;
    Thread* thread_;
    vector<string> ListeEvent_;
    std::vector<ThreadableInterface*> threadables_;
    TCPSocket* ServerSocket_;
    unsigned short echoServPort_;
    void Listen();
    Serializer *serializer_;
    Deserializer *deserializer_;
    Demultiplexeur* demultiplexeur_;
};
}
#endif // CLIENT_H