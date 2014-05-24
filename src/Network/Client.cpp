#include "Client.h"
namespace Network{
Client::Client(Ip ip, Port port, EventQueue eventqueue)
{

   this->echoServPort= Socket::resolveService(port, "tcp");
    try
    {

         ServerSocket=new TCPSocket(ip, echoServPort);



    }
    catch(SocketException &e)
    {
        std::cerr << e.what() << std::endl;
        //exit(1);
    }

}

Client::~Client()
{
    //dtor
}


void Client::SetSerializer(Serializer *serializer){

this->serializer=serializer;

}

Serializer * Client::GetSerializer(){

return this->serializer;

}

void Client::SetDeserializer(Deserializer * deserializer){

this->deserializer=deserializer;

}

Deserializer * Client::GetDeserializer(){

return this->deserializer;

}

}
