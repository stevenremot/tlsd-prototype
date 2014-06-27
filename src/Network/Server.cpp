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
#include "Server.h"

#include <sstream>

#include "../Physics/EntityPositionChangedEvent.h"
#include "EventSerialization.h"

using Threading::ThreadableInterface;
using Threading::Thread;

namespace Network
{
    Server::Server(string  port, Event::EventQueue& eventQueue):
        eventQueue_(eventQueue)
    {

        ///Initialisation des pointeurs

        // this->serializer_=NULL;
        // this->deserializer_=NULL;
        this->demultiplexeur_=new Demultiplexeur(&(this->ListeClient_),&(this->ListeEvent_));

        unsigned short echoServPort = Socket::resolveService(port, "tcp");
        ///Creation ServerSocket

        this->servSock_ = new TCPServerSocket(echoServPort);


        /// Instancie la classe AcceptClient
        acceptclient_ = new AcceptClient(servSock_,&ListeClient_, eventQueue);


        /// Création de thread pour AcceptClient

        threadables_.push_back(acceptclient_);
        threadables2_.push_back(demultiplexeur_);
        this->thread_=new Thread(threadables_, 2);
        this->thread_->start();
        this->thread2_=new Thread(threadables2_, 2);
        this->thread2_->start();
    }

    Server::~Server()
    {
        // this->serializer_=NULL;
        // this->deserializer_=NULL;
        this->thread_->stop();
        this->thread2_->stop();
        delete thread_;
        delete thread2_;
        delete demultiplexeur_;

        for (unsigned int i = 0; i < ListeClient_.size(); i++)
        {
            delete ListeClient_[i];
        }

        delete servSock_;
    }

    // void Server::SetSerializer(Serializer *serializer)
    // {

    //     this->serializer_=serializer;

    // }

    // Serializer * Server::GetSerializer()
    // {

    //     return this->serializer_;

    // }

    // void Server::SetDeserializer(Deserializer * deserializer)
    // {

    //     this->deserializer_=deserializer;

    // }

    // Deserializer * Server::GetDeserializer()
    // {

    //     return this->deserializer_;

    // }

    void Server::SendEvent(const Event::Event& event)
    {
        std::stringstream sstream;
        if (serializeEvent(sstream, event))
        {
            this->ListeEvent_.push_back(sstream.str());
        }
    }

    void Server::call(const Event::Event& event)
    {
        SendEvent(event);
    }

    void Server::registerListeners(Event::ListenerRegister& reg)
    {
        reg.put(Physics::EntityPositionChangedEvent::Type, this);
    }

    void Server::unregisterListeners(Event::ListenerRegister& reg)
    {
        reg.remove(this);
    }
}
