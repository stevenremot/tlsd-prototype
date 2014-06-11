#ifndef PHYSICS_INITCOLLISIONENGINEEVENT_H
#define PHYSICS_INITCOLLISIONENGINEEVENT_H

#include <irrlicht/ISceneManager.h>
#include "../Event/Event.h"

namespace Physics
{
    class InitCollisionEngineEvent : public Event::Event
    {
        public:
            static const Event::Type TYPE;

            InitCollisionEngineEvent(irr::scene::ISceneManager* manager):
                Event::Event(TYPE),
                manager_(manager)
                {}

            irr::scene::ISceneManager* getManager() const
            {
                return manager_;
            }

        private:
            irr::scene::ISceneManager* manager_;
    };
}

#endif // PHYSICS_INITCOLLISIONENGINEEVENT_H
