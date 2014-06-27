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
#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "PracticalSocket.h"
#include "AcceptClient.h"
#include "Demultiplexeur.h"
#include "../Threading/ThreadableInterface.h"
#include "../Threading/Thread.h"
#include "../Threading/ConcurrentRessource.h"
#include "../Event/EventListenerInterface.h"
#include "../Event/EventQueue.h"
#include "../Event/ListenerRegister.h"
#include "ServerConnectionClosedCallback.h"

typedef string Port;
// typedef int Serializer;
// typedef int Deserializer;

namespace Network
{
    class Server: public Event::EventListenerInterface
    {
    public:
        Server(string port, Event::EventQueue& eventQueue);
        virtual ~Server();
        // void SetSerializer(Serializer* serializer);
        // Serializer* GetSerializer();
        // void SetDeserializer(Deserializer* deserializer );
        // Deserializer* GetDeserializer();
        void SendEvent(const Event::Event& event);

        virtual void call(const Event::Event& event);

        void registerListeners(Event::ListenerRegister& reg);
        void unregisterListeners(Event::ListenerRegister& reg);

        TCPServerSocket& getSocket()
        {
            return *servSock_;
        }

        friend class ServerConnectionClosedCallback;

    private:
        Threading::Thread* thread_, *thread2_;
        TCPServerSocket* servSock_;
        Threading::ConcurrentRessource< vector<TCPSocket*> > ListeClient_;
        vector<Threading::Thread*> clientThreads_;
        vector<string> ListeEvent_;
        void Listen();
        void Accept();
        // Serializer *serializer_;
        // Deserializer *deserializer_;
        Demultiplexeur *demultiplexeur_;
        AcceptClient* acceptclient_;
        std::vector<ThreadableInterface*> threadables_;
        std::vector<ThreadableInterface*> threadables2_;
        Event::EventQueue& eventQueue_;

        void closeClient(TCPSocket* client);
    };
}
#endif // SERVER_H
