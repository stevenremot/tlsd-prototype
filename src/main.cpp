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

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Event/EventManager.h"
#include "Ecs/World.h"
#include "Threading/ThreadableInterface.h"
#include "Threading/Thread.h"

#include "Geometry/Vec2D.h"
#include "Geometry/Vec3D.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

//////////////////////////////////////////////////
// Test events
//////////////////////////////////////////////////

class QuitEvent: public Event::Event
{
public:
    static const Event::Type TYPE;
    QuitEvent(): Event::Event(TYPE)
    {}
};
const Event::Event::Type QuitEvent::TYPE = "quit";

class PrintEvent: public Event::Event
{
public:
    static const Type TYPE;

    PrintEvent(char c): Event::Event(TYPE), c_(c)
    {}

    char getChar() const
    {
        return c_;
    }

private:
    char c_;
};

const Event::Event::Type PrintEvent::TYPE = "print";

class PrintListener: public Event::EventListenerInterface
{
public:
    virtual void call(const Event::Event & event)
    {
        cout << static_cast<const PrintEvent &>(event).getChar();
    }
};

static bool loop = true;

class QuitListener: public Event::EventListenerInterface
{
public:
    virtual void call(const Event::Event & event)
    {
        loop = false;
    }
};

void testEvents()
{
    Event::EventManager m;
    Event::ListenerRegister & reg = m.getListenerRegister();

    reg.put(PrintEvent::TYPE, new PrintListener());
    reg.put(QuitEvent::TYPE, new QuitListener());

    vector<Threading::ThreadableInterface*> threadables;
    threadables.push_back(&m);

    Threading::Thread eventThread(threadables, 1);
    eventThread.start();

    Event::EventQueue & queue = m.getEventQueue();

    queue.push(new PrintEvent('h'));
    queue.push(new PrintEvent('e'));
    queue.push(new PrintEvent('l'));
    queue.push(new PrintEvent('l'));
    queue.push(new PrintEvent('o'));
    queue.push(new QuitEvent());

    while (loop)
    {
        cout << ".";
        Threading::sleep(0, 500);
    }

    eventThread.stop();
}

class MessageComponent: public Ecs::Component
{
public:
    static const Ecs::Component::Type Type;
    MessageComponent(const char * message): Component(Type),
                                            message_(message)
    {}

    const char * getMessage() const
    {
        return message_;
    }

private:
    const char * message_;
};

const Ecs::Component::Type MessageComponent::Type = "message";

void testEcs()
{
    Ecs::World w = Ecs::World();

    Ecs::Entity entity1 = w.createEntity();
    w.addComponent(entity1, new MessageComponent("Hello world !"));
    Ecs::Entity entity2 = w.createEntity();

    Ecs::ComponentGroup::ComponentTypeCollection types;
    types.insert(MessageComponent::Type);

    Ecs::ComponentGroup prototype(types);
    Ecs::World::ComponentGroupCollection groups = w.getComponents(prototype);

    Ecs::World::ComponentGroupCollection::iterator group;
    for (group = groups.begin(); group != groups.end(); ++group)
    {
        cout << group->getEntity() << " says ";
        cout << static_cast<MessageComponent &>(group->getComponent(MessageComponent::Type)).getMessage() << endl;
    }
}

void testVectors()
{
    Geometry::Vec2Df v1(1, 2);
    Geometry::Vec2Df v2(4, 5);

    cout << v1 + v2 << endl;
    cout << v1 - v2 << endl;
    cout << v1 * v2 << endl;
    cout << v1 * 4 << endl;
    cout << -v1 << endl;
    cout << v1.getLength() << endl;

    Geometry::Vec3Df v3(1, 2, 3);
    Geometry::Vec3Df v4(4, 5, 6);

    cout << v3 + v4 << endl;
    cout << v3 - v4 << endl;
    cout << v3 * v4 << endl;
    cout << v3 * 4 << endl;
    cout << -v3 << endl;
    cout << v3.getLength() << endl;
}

int main() {
    // testEvents();
    // testEcs();
    testVectors();

    return 0;
}
