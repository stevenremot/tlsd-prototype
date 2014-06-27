#include "network.h"

#include "../Threading/Thread.h"
#include "../Event/EventManager.h"

using std::cout;
using std::endl;
using Network::Server;
using Network::Client;
namespace NetworkTest
{

    void TestNetwork()
    {

        /// Faire un scénario de test Client/Server
        Event::EventManager em;
        Server* server =new Server("1234",NULL);
        string str="127.0.0.1";
        Client* client1 = new Client (str,"1234",em.getEventQueue());
        Client* client2 = new Client (str,"1234",em.getEventQueue());
        int i=0;
        while(i<3)
        {
            Threading::sleep(1, 0);
            client1->SendEvent("Client1");
            client2->SendEvent("Client2");
            server->SendEvent("Server");
            i++;
        }

        std::cout<<"Network part done"<<std::endl;
    };


}
