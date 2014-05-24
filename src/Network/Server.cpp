#include "Server.h"

using Threading::ThreadableInterface;
using Threading::Thread;
namespace Network
{
Server::Server(Port port, EventQueue *eventqueue)
{
///Initialisation des pointeurs

    this->serializer=NULL;
    this->deserializer=NULL;


    unsigned short echoServPort = Socket::resolveService((string) port, "tcp");
///Creation ServerSocket

    this->servSock = new TCPServerSocket(echoServPort);


/// Instancie la classe AcceptClient
    AcceptClient* acceptclient = new AcceptClient(servSock,&ListeClient);


/// Création de thread pour AcceptClient
    std::vector<ThreadableInterface*> threadables;

    threadables.push_back(acceptclient);

    this->thread= new Thread(threadables, 2);
    this->thread->start();

}

Server::~Server()
{
    this->serializer=NULL;
    this->deserializer=NULL;
    this->thread->stop();
}

void Server::SetSerializer(Serializer *serializer)
{

    this->serializer=serializer;

}

Serializer * Server::GetSerializer()
{

    return this->serializer;

}

void Server::SetDeserializer(Deserializer * deserializer)
{

    this->deserializer=deserializer;

}

Deserializer * Server::GetDeserializer()
{

    return this->deserializer;

}

}
