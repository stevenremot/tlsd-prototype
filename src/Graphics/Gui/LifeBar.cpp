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

#include "LifeBar.h"

#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>

#include "../../Ecs/ComponentGroup.h"
#include "../../Input/PlayerComponent.h"
#include "../../Character/GroupComponent.h"
#include "../../Character/CharacterComponent.h"
#include "../../Character/GroupUtil.h"

using Threading::getConcurrentReader;
using Threading::ConcurrentReader;
using Character::CharacterComponent;

namespace Graphics
{
    namespace Gui
    {
        void drawLifeBar(
            unsigned int current,
            unsigned int max,
            const irr::core::rect<irr::s32>& rect,
            irr::video::IVideoDriver* driver
        ) {
            const irr::s32 baseX = rect.UpperLeftCorner.X;
            const irr::s32 baseY = rect.UpperLeftCorner.Y;
            const irr::s32 baseW = rect.getWidth();
            const irr::s32 baseH = rect.getHeight();

            driver->draw2DRectangle(
                irr::video::SColor(128, 0, 0, 0),
                rect
            );

            const float ratio =
                static_cast<float>(current) / static_cast<float>(max);

            driver->draw2DRectangle(
                irr::video::SColor(255, 255, 0, 0),
                irr::core::rect<irr::s32>(
                    baseX,
                    baseY,
                    baseX + static_cast<float>(baseW) * ratio,
                    baseY + baseH
                )
            );

            driver->draw2DRectangleOutline(
                rect,
                irr::video::SColor(255, 255, 255, 255)
            );
        }

        void LifeBar::draw()
        {
            Threading::ConcurrentWriter<Ecs::World> world = world_->getWriter();
            irr::video::IVideoDriver* driver = Environment->getVideoDriver();

            Ecs::ComponentGroup::ComponentTypeCollection types;
            types.insert(Input::PlayerComponent::Type);
            Ecs::ComponentGroup prototype(types);

            Ecs::World::ComponentGroupCollection groups =
                world->getComponents(prototype);

            if (!groups.empty())
            {
                Ecs::ComponentGroup& group = groups.front();

                Ecs::Entity groupEntity =
                    getConcurrentReader<Ecs::Component, CharacterComponent>(
                        group.getComponent(CharacterComponent::Type)
                    )->getGroup();

                unsigned int maxHealth = Character::computeMaxHealth(
                    world,
                    groupEntity
                );

                unsigned int currentHealth =
                    getConcurrentReader<Ecs::Component, Character::GroupComponent>(
                        world->getEntityComponent(
                            groupEntity,
                            Character::GroupComponent::Type
                        )
                    )->getCurrentHealth();

                drawLifeBar(currentHealth, maxHealth, AbsoluteClippingRect, driver);
            }
        }
    }
}
