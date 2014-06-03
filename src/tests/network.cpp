#include "network.h"


using std::cout;
using std::endl;
using Network::Server;
using Network::Client;
namespace NetworkTest
{

void TestNetwork()
{

/// Faire un scénario de test Client/Server

    Server* server =new Server("1234",NULL );
    string str="127.0.0.1";
    Client* client1 = new Client (str,"1234",NULL);
    Client* client2 = new Client (str,"1234",NULL);
int i=0;
    while(i<3)
    {
        Sleep(1000);
        client1->SendEvent("Client1");
        client2->SendEvent("Client2");
        server->SendEvent("Server");
    i++;
    }

    std::cout<<"Network part done"<<std::endl;
};


}
