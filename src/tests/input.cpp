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

#include "input.h"

#include <iostream>

#include "../Input/PlayerSystem.h"
#include "../Character/ActionPerformedEvent.h"
#include "../Character/MoveAction.h"
#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"
#include "../Physics/MovementComponent.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/AnimationComponent.h"
#include "../Input/PlayerComponent.h"
#include "../Input/Events.h"

#include "../Geometry/IrrlichtConversions.h"

namespace InputTest
{
    class ActionEventListener: public Event::EventListenerInterface
    {
    public:
        virtual void call(const Event::Event& event)
        {
            if (event.getType() == Character::ActionPerformedEvent::Type)
            {
                std::cout << "Performed action" << std::endl;
                const Character::ActionPerformedEvent& e =
                    dynamic_cast<const Character::ActionPerformedEvent&>(event);

                const Ecs::Entity& entity = e.getEntity();
                const Character::Action& action = e.getAction();

                std::cout << "On entity : " << entity << std::endl;

                if (action.getType() == Character::MoveAction::Type)
                {
                    const Character::MoveAction& a =
                        dynamic_cast<const Character::MoveAction&>(action);

                    std::cout << "Moved in direction : " << a.getDirection() << std::endl;
                }
            }
            else
            {
                std::cout << "Performed " << event.getType() << std::endl;
            }
        }
    };

    void testPlayerSystem()
    {
        Event::EventManager em;

        Threading::ConcurrentRessource<Ecs::World> w(new Ecs::World(em.getEventQueue()));

        {
            Threading::ConcurrentWriter<Ecs::World> ww = w.getWriter();

            const Ecs::Entity& entity = ww->createEntity();
            ww->addComponent(entity, new Geometry::PositionComponent(Geometry::Vec3Df()));
            ww->addComponent(entity, new Geometry::RotationComponent(Geometry::Vec3Df(0, 0, 90)));
            ww->addComponent(entity, new Physics::MovementComponent(Geometry::Vec3Df()));
            ww->addComponent(
                entity,
                new Graphics::Render::RenderableComponent(Graphics::Render::Model3D())
            );
            Graphics::Render::AnimationMap animMap;
            animMap[Graphics::Render::Idle] =
                Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
            animMap[Graphics::Render::Walk] =
                Graphics::Render::AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
            std::map<Character::Action::Type, Graphics::Render::AnimationType> animByAction;
            //       animByAction[0] = Graphics::Render::Idle;
            animByAction[Character::MoveAction::Type] = Graphics::Render::Walk;

            ww->addComponent(
                entity,
                new Graphics::Render::AnimationComponent(animMap, animByAction)
            );

            ww->addComponent(
                entity,
                new Input::PlayerComponent
            );
        }

        Input::PlayerSystem ps(w, em.getEventQueue());

        ps.registerListeners(em.getListenerRegister());

        ActionEventListener lis;
        em.getListenerRegister().put(Character::ActionPerformedEvent::Type, &lis);

        em.getEventQueue() << new Input::MoveEvent(Geometry::Vec2Df(0.0, 1.0));

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(&em);
        threadables.push_back(&ps);

        Threading::Thread t(threadables, 60);
        t.start();

        Threading::sleep(0, 500);

        t.stop();
    }

    void testCoordinates()
    {
        Geometry::Vec3Df dir(1,0,0);
        Geometry::Vec2Df dir2d(dir.getX(), dir.getY());
        std::cout << dir2d.getOrientation() * 180.0 / M_PI << std::endl;
        std::cout << "irrlicht: " << Geometry::fromIrrVector3df(
                      Geometry::fromVec3Df(dir).getHorizontalAngle().rotationToDirection())
                  << std::endl;

        dir = Geometry::Vec3Df(0,1,0);
        dir2d = Geometry::Vec2Df(dir.getX(), dir.getY());
        std::cout << dir2d.getOrientation() * 180.0 / M_PI << std::endl;
        std::cout << "irrlicht: " << Geometry::fromIrrVector3df(
                      Geometry::fromVec3Df(dir).getHorizontalAngle().rotationToDirection())
                  << std::endl;

        dir = Geometry::Vec3Df(-1,0,0);
        dir2d = Geometry::Vec2Df(dir.getX(), dir.getY());
        std::cout << dir2d.getOrientation() * 180.0 / M_PI << std::endl;
        std::cout << "irrlicht: " << Geometry::fromIrrVector3df(
                      Geometry::fromVec3Df(dir).getHorizontalAngle().rotationToDirection())
                  << std::endl;

        dir = Geometry::Vec3Df(0,-1,0);
        dir2d = Geometry::Vec2Df(dir.getX(), dir.getY());
        std::cout << dir2d.getOrientation() * 180.0 / M_PI << std::endl;
        std::cout << "irrlicht: " << Geometry::fromIrrVector3df(
                      Geometry::fromVec3Df(dir).getHorizontalAngle().rotationToDirection())
                  << std::endl;
    }
}
