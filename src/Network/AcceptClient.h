#ifndef ACCEPTCLIENT_H
#define ACCEPTCLIENT_H

#include "PracticalSocket.h"
#include <vector>
#include <iostream>

#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;
namespace Network
{
class AcceptClient : public ThreadableInterface
{
public:
    AcceptClient(TCPServerSocket *Server,std::vector<TCPSocket*> *ListeClient);
    virtual ~AcceptClient();
    void run(void);
protected:
private:
    TCPServerSocket *Server;
    vector<TCPSocket*> *ListeClient;
};
}
#endif // ACCEPTCLIENT_H
