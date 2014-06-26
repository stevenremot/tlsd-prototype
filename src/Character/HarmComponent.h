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

#ifndef CHARACTER_HARM_COMPONENT_H
#define CHARACTER_HARM_COMPONENT_H

#include "../Ecs/Component.h"

namespace Character
{
    /**
     * Component for entities that can cause damages to others.
     */
    class HarmComponent: public Ecs::Component
    {
    public:
        static const Type Type;

        HarmComponent(unsigned int damages): Component(Type), damages_(damages)
        {}

        virtual Component* clone() const;

        const std::vector<Component::Type>& getDependentComponents();

        float getDamages() const;

    private:
        static std::vector<Component::Type> dependentComponents_;
        unsigned int damages_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
