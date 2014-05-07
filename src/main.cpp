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

#include "Event/EventManager.h"
#include "Ecs/World.h"

using std::cout;
using std::endl;

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

int main() {
    // Event test
    Event::EventManager m;
    Event::ListenerRegister & reg = m.getListenerRegister();

    reg.put(PrintEvent::TYPE, new PrintListener());
    reg.put(QuitEvent::TYPE, new QuitListener());

    Event::EventQueue & queue = m.getEventQueue();

    queue.push(new PrintEvent('h'));
    queue.push(new PrintEvent('e'));
    queue.push(new PrintEvent('l'));
    queue.push(new PrintEvent('l'));
    queue.push(new PrintEvent('o'));
    queue.push(new QuitEvent());

    while (loop)
    {
        m.run();
    }

    // Ecs test
    cout << endl;
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

    return 0;
}
