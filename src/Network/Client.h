#ifndef CLIENT_H
#define CLIENT_H
#include "PracticalSocket.h"
#include <pthread.h>
#include <iostream>


#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;

typedef string Port;
typedef string Ip;
typedef int EventQueue;
typedef int Event2;
typedef int Serializer;
typedef int Deserializer;

namespace Network{
class Client
{
    public:
        Client(Ip ip, Port port, EventQueue eventqueue);
        virtual ~Client();
        void SetSerializer(Serializer *serializer);
        Serializer *GetSerializer();
        void SetDeserializer(Deserializer *deserializer );
        Deserializer *GetDeserializer();
        void SendEvent(Event2 event);

    protected:
    private:
TCPSocket* ServerSocket;
        unsigned short echoServPort;
        void Listen();
        Serializer *serializer;
        Deserializer *deserializer;
};
}
#endif // CLIENT_H
