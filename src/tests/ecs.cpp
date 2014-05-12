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

using std::cout;
using std::endl;

#include "../Ecs/World.h"

namespace EcsTest
{

    const Ecs::Component::Type MessageComponent::Type = "message";

    void testEcs()
    {
        Ecs::World w = Ecs::World();

        Ecs::Entity entity1 = w.createEntity();
        w.addComponent(entity1, new MessageComponent("Hello world !"));
        w.createEntity();

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
}
