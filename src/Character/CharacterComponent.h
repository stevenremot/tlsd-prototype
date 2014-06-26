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

#ifndef CHARACTER_CHARACTERCOMPONENT_H
#define CHARACTER_CHARACTERCOMPONENT_H

#include "../Ecs/Entity.h"
#include "../Ecs/Component.h"
#include "../Graphics/Render/AnimationComponent.h"
#include "StatisticsComponent.h"

namespace Character
{

    /**
    *   Component which describes a game character
    */
    class CharacterComponent : public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        static std::vector<Ecs::Component::Type> Dependencies;

        CharacterComponent(float walkingSpeed, const Ecs::Entity& group):
            Component(Type),
            walkingSpeed_(walkingSpeed),
            group_(group),
            attackArea_(),
            isAttacking_(false)
        {}

        virtual Component* clone() const
        {
            return new CharacterComponent(walkingSpeed_, group_);
        }

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
        {
            if (Dependencies.empty())
            {
                Dependencies.push_back(Graphics::Render::AnimationComponent::Type);
                Dependencies.push_back(StatisticsComponent::Type);
            }
            return Dependencies;
        }

        float getWalkingSpeed() const
        {
            return walkingSpeed_;
        }

        const Ecs::Entity& getGroup() const
        {
            return group_;
        }

        void setGroup(const Ecs::Entity& group)
        {
            group_ = group;
        }

        bool isAttacking() const
        {
            return isAttacking_;
        }

        void setAttacking(bool isAttacking)
        {
            isAttacking_ = isAttacking;
        }

        const Ecs::Entity& getAttackArea() const
        {
            return attackArea_;
        }

        void setAttackArea(const Ecs::Entity& attackArea)
        {
            attackArea_ = attackArea;
        }

    private:
        // TODO replace with statistics field ?
        float walkingSpeed_;
        Ecs::Entity group_;
        Ecs::Entity attackArea_;
        bool isAttacking_;
    };
}

#endif // CHARACTER_CHARACTERCOMPONENT_H

// Emacs local variables
// Local variables:
// mode: c++
// End:
