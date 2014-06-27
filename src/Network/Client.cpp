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
namespace Network
{
    Client::Client(Ip ip, string port, Event::EventQueue& eventQueue):
        serializer_(NULL),
        deserializer_(NULL),
        demultiplexeur_(NULL)
    {

        connected_ = false;

        this->echoServPort_= Socket::resolveService(port, "tcp");
        try
        {
            this->ServerSocket_=new TCPSocket(ip, echoServPort_);
            this->listener_=new Listener((&this->ListeEvent_),this->ServerSocket_);
            connected_=true;
            //this->demultiplexeur=new Demultiplexeur(NULL,this->ListeEvent,ServerSocket);


            threadables_.push_back(listener_);
            this->thread_=new Thread(threadables_, 2);
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
        //dtor
    }


    void Client::SetSerializer(Serializer *serializer)
    {

        this->serializer_=serializer;

    }

    Serializer * Client::GetSerializer()
    {

        return this->serializer_;

    }

    void Client::SetDeserializer(Deserializer * deserializer)
    {

        this->deserializer_=deserializer;

    }

    Deserializer * Client::GetDeserializer()
    {

        return this->deserializer_;

    }

    void Client::SendEvent(Event2 event)
    {

        if(connected_==true)
        {
            ServerSocket_->send(event.c_str(),event.size()+1);
        }


    }

}
