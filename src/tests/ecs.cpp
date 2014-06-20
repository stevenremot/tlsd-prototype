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

#include "ecs.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

#include "../Ecs/World.h"

#include "../Event/EventManager.h"

namespace EcsTest
{
    class MessageComponent: public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;
        static const std::vector<Ecs::Component::Type> Dependencies;

        MessageComponent(const string& message): Component(Type),
                                                 message_(message)
        {}

        const string& getMessage() const
        {
            return message_;
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            return Dependencies;
        }

    private:
        string message_;
    };

    const Ecs::Component::Type MessageComponent::Type = "message";
    const std::vector<Ecs::Component::Type> MessageComponent::Dependencies =
        std::vector<Ecs::Component::Type>();


    class DummyComponent: public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;
        static const std::vector<Ecs::Component::Type> Dependencies;

        DummyComponent(): Component(Type)
        {}

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            return Dependencies;
        }
    };

    const Ecs::Component::Type DummyComponent::Type = "dummy";
    const std::vector<Ecs::Component::Type> DummyComponent::Dependencies;

    void testEcs()
    {
        Event::EventManager m = Event::EventManager();

        Ecs::World w = Ecs::World(m.getEventQueue());

        Ecs::Entity entity1 = w.createEntity();
        w.addComponent(entity1, new MessageComponent("Hello world !"));
        w.addComponent(entity1, new DummyComponent());
        w.createEntity();

        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(MessageComponent::Type);

        Ecs::ComponentGroup prototype(types);
        Ecs::World::ComponentGroupCollection groups = w.getComponents(prototype);

        Ecs::World::ComponentGroupCollection::iterator group;
        for (group = groups.begin(); group != groups.end(); ++group)
        {
            cout << group->getEntity() << " says ";
            cout << static_cast<const MessageComponent &>(*group->getComponent(MessageComponent::Type).getReader()).getMessage() << endl;
        }
    }

    void testSharedEntity()
    {
        bool failed = false;

        Event::EventManager em;
        Ecs::World world(em.getEventQueue());

        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(MessageComponent::Type);

        Ecs::ComponentGroup prototype(types);
        Ecs::World::ComponentGroupCollection groups =
            world.getComponents(prototype);

        if (!groups.empty())
        {
            cout << "SharedEntity : wtf ?!" << endl;
            failed = true;
        }


        {
            Ecs::SharedEntity entity = world.createSharedEntity();
            world.addComponent(entity.getEntity(), new MessageComponent("yo"));
            Ecs::World::ComponentGroupCollection groups =
                world.getComponents(prototype);

            if (groups.size() != 1)
            {
                cout << "SharedEntity : expected to be 1, is " << groups.size()
                     << endl;
                failed = true;
            }
        }

        groups = world.getComponents(prototype);

        if (!groups.empty())
        {
            cout << "SharedEntity : expected to be empty, is " << groups.size()
                 << endl;
            failed = true;
        }

        if (!failed)
        {
            cout << "SharedEntity : All tests passed." << endl;
        }
    }
}
