#ifndef SERVER_H
#define SERVER_H
#include "PracticalSocket.h"
#include "AcceptClient.h"
#include "../Threading/ThreadableInterface.h"
#include "../Threading/Thread.h"

using Threading::ThreadableInterface;
using Threading::Thread;
typedef string Port;
typedef int EventQueue;
typedef int Event2;
typedef int Serializer;
typedef int Deserializer;

namespace Network
{
class Server : public ThreadableInterface
{
public:
    Server(Port port, EventQueue *eventqueue);
    virtual ~Server();
    void SetSerializer(Serializer* serializer);
    Serializer* GetSerializer();
    void SetDeserializer(Deserializer* deserializer );
    Deserializer* GetDeserializer();

protected:
private:
    Thread* thread;
    TCPServerSocket* servSock;
    vector<TCPSocket*> ListeClient;
    void Listen();
    void Accept();
    Serializer *serializer;
    Deserializer *deserializer;


};
}
#endif // SERVER_H
