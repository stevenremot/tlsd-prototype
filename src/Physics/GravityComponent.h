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

#ifndef PHYSICS_GRAVITY_COMPONENT_H
#define PHYSICS_GRAVITY_COMPONENT_H

#include "../Ecs/Component.h"

namespace Physics
{
    /**
     * Component for entities sensibles to gravity
     */
    class GravityComponent: public Ecs::Component
    {
    public:
        static const Ecs::Component::Type Type;

        GravityComponent(float weight): Component(Type), weight_(weight)
        {}

        virtual const std::vector<Ecs::Component::Type>& getDependentComponents();

        float getWeight() const
        {
            return weight_;
        }

        void setWeight(float weight)
        {
            weight_ = weight;
        }

    private:
        static std::vector<Ecs::Component::Type> dependentTypes_;
        float weight_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
