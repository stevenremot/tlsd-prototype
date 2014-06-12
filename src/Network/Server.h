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
#ifndef SERVER_H
#define SERVER_H
#include "PracticalSocket.h"
#include "AcceptClient.h"
#include "Demultiplexeur.h"
#include "../Threading/ThreadableInterface.h"
#include "../Threading/Thread.h"

using Threading::ThreadableInterface;
using Threading::Thread;
typedef string Port;
typedef int EventQueue;
typedef string Event2;
typedef int Serializer;
typedef int Deserializer;

namespace Network
{
class Server
{
public:
    Server(string port, EventQueue* eventqueue);
    virtual ~Server();
    void SetSerializer(Serializer* serializer);
    Serializer* GetSerializer();
    void SetDeserializer(Deserializer* deserializer );
    Deserializer* GetDeserializer();
    void SendEvent(Event2 event);

protected:
private:
    Thread* thread_, *thread2_;
    TCPServerSocket* servSock_;
    vector<TCPSocket*> ListeClient_;
    vector<string> ListeEvent_;
    void Listen();
    void Accept();
    Serializer *serializer_;
    Deserializer *deserializer_;
    Demultiplexeur *demultiplexeur_;
    AcceptClient* acceptclient_;
    std::vector<ThreadableInterface*> threadables_;
    std::vector<ThreadableInterface*> threadables2_;

};
}
#endif // SERVER_H
