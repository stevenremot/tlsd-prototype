#ifndef PHYSICS_ENTITYPOSITIONCHANGED_H
#define PHYSICS_ENTITYPOSITIONCHANGED_H

#include "../Event/Event.h"
#include "../Ecs/Entity.h"
#include "../Geometry/Vec3D.h"

namespace Physics
{
    class EntityPositionChangedEvent : public Event::Event
    {
        public:
            static const Event::Event::Type TYPE;

            EntityPositionChangedEvent(const Ecs::Entity& entity, const Geometry::Vec3Df& position):
                Event::Event(TYPE),
                entity_(entity),
                position_(position)
                {}

            const Ecs::Entity& getEntity()
            {
                return entity_;
            }

            const Geometry::Vec3Df& getPosition()
            {
                return position_;
            }


        private:
            Ecs::Entity entity_;
            Geometry::Vec3Df position_;

    };
}

#endif // PHYSICS_ENTITYPOSITIONCHANGED_H
