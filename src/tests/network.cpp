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

#include "network.h"

#include "../Event/EventManager.h"
#include "../Threading/Thread.h"
#include "../Physics/EntityPositionChangedEvent.h"

using std::cout;
using std::endl;
using Network::Server;
using Network::Client;
namespace NetworkTest
{
    class DummyListener: public Event::EventListenerInterface
    {
    public:
        virtual void call(const Event::Event& event)
        {
            std::cout << "Event : " << event.getType() << std::endl;

            if (event.getType() == Physics::EntityPositionChangedEvent::Type)
            {
                const Physics::EntityPositionChangedEvent& evt =
                    dynamic_cast<const Physics::EntityPositionChangedEvent&>(event);

                std::cout << "Entity : " << evt.getEntity() << std::endl;
                std::cout << "Pos : " << evt.getPosition() << std::endl;
            }
        }

        void registerListeners(Event::ListenerRegister& reg)
        {
            reg.put(Physics::EntityPositionChangedEvent::Type, this);
        }
    };

    void TestNetwork()
    {

        /// Faire un scénario de test Client/Server
        Event::EventManager em;

        Server* server = new Server("1234", em.getEventQueue());
        string str = "127.0.0.1";
        Client* client1 = new Client (str,"1234",em.getEventQueue());
        Client* client2 = new Client (str,"1234",em.getEventQueue());
        int i=0;

        DummyListener lis;
        lis.registerListeners(em.getListenerRegister());

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(&em);
        Threading::Thread eventThread(threadables, 10);
        eventThread.start();

        while(i<30)
        {
            if (i == 2)
            {
                delete client1;
            }

            Threading::sleep(1, 0);
            // client1->SendEvent("Client1");
            // client2->SendEvent("Client2");
            server->SendEvent(Physics::EntityPositionChangedEvent(
                1,
                Geometry::Vec3Df(1, 2, 3)
            ));
            i++;
        }

        eventThread.stop();

        std::cout<<"Network part done"<<std::endl;
    };


}
