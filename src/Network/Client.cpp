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
#include "Client.h"

#include <sstream>

#include "EventSerialization.h"
#include "../Physics/EntityPositionChangedEvent.h"

namespace Network
{
    Client::Client(Ip ip, string port, Event::EventQueue& eventQueue):
        // serializer_(NULL),
        // deserializer_(NULL),
        demultiplexeur_(NULL),
        eventQueue_(eventQueue)
    {

        connected_ = false;

        this->echoServPort_= Socket::resolveService(port, "tcp");
        try
        {
            this->ServerSocket_ = new TCPSocket(ip, echoServPort_);
            this->listener_= new Listener(
                (&this->ListeEvent_),
                this->ServerSocket_,
                eventQueue
            );
            connected_=true;
            // demultiplexeur_ = new Demultiplexeur(, ListeEvent_);


            threadables_.push_back(listener_);
            this->thread_ = new Threading::Thread(threadables_, 2);
            this->thread_->start();

        }
        catch(SocketException &e)
        {
            connected_=false;
            std::cerr << e.what() << std::endl;
        }
    }

    Client::~Client()
    {
        delete ServerSocket_;
        delete demultiplexeur_;
        thread_->stop();
        delete thread_;
        delete listener_;
    }

    // void Client::SetSerializer(Serializer *serializer)
    // {

    //     this->serializer_=serializer;

    // }

    // Serializer * Client::GetSerializer()
    // {

    //     return this->serializer_;

    // }

    // void Client::SetDeserializer(Deserializer * deserializer)
    // {

    //     this->deserializer_=deserializer;

    // }

    // Deserializer * Client::GetDeserializer()
    // {

    //     return this->deserializer_;

    // }

    void Client::SendEvent(const Event::Event& event)
    {
        std::stringstream sstream;
        if (serializeEvent(sstream, event))
        {
            ServerSocket_->send(sstream.str().c_str(), sstream.str().size());
        }
    }



    void Client::call(const Event::Event& event)
    {
        SendEvent(event);
    }

    void Client::registerListeners(Event::ListenerRegister& reg)
    {
        reg.put(Physics::EntityPositionChangedEvent::Type, this);
    }

    void Client::unregisterListeners(Event::ListenerRegister& reg)
    {
        reg.remove(this);
    }
}
