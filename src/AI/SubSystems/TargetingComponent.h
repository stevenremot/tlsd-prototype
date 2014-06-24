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

#ifndef AI_SUBSYSTEM_TARGETINGCOMPONENT_H
#define AI_SUBSYSTEM_TARGETINGCOMPONENT_H

//#include "../AiComponent.h"
#include "../MemoryComponent.h"

#include "../../Ecs/Component.h"
#include "../../Geometry/Vec3D.h"

namespace AI
{
    namespace Subsystem
    {
        class TargetingComponent : public Ecs::Component
        {
        public:

            static const Ecs::Component::Type Type;

            TargetingComponent() : Component(Type), hasValidTarget_(false) {}

            virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
            {
                if(Dependencies.empty())
                {
                    //Dependencies.push_back(AiComponent::Type);
                    Dependencies.push_back(MemoryComponent::Type);
                }
                return Dependencies;
            }

            /**
             * return true if the target isn't too far from the target in the targeting component
             */
            bool isTargetValid(const Geometry::Vec3Df& targetPosition) const;

            Geometry::Vec3Df getTargetPosition() const {return targetPosition_;}
            void setTargetPosition(const Geometry::Vec3Df& targetPosition) {targetPosition_ = targetPosition;}

            Ecs::Entity getTargetEntity() const {return targetEntity_;}
            void setTargetEntity(Ecs::Entity targetEntity) {targetEntity_ = targetEntity;}

            bool hasValidTarget() const {return hasValidTarget_;}
            void setHasValidTarget(bool hasValidTarget) {hasValidTarget_ = hasValidTarget;}

        private:
            static std::vector<Ecs::Component::Type> Dependencies;

            Geometry::Vec3Df targetPosition_;
            Ecs::Entity targetEntity_;
            bool hasValidTarget_;
        };
    }
}

#endif // AI_SUBSYSTEM_TARGETINGCOMPONENT_H
