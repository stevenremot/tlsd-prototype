#ifndef PHYSICS_INITCOLLISIONENGINEEVENT_H
#define PHYSICS_INITCOLLISIONENGINEEVENT_H

#include <irrlicht/ISceneManager.h>
#include "../Event/Event.h"
#include "../Graphics/Render/SceneData.h"

namespace Physics
{
    class InitCollisionEngineEvent : public Event::Event
    {
        public:
            static const Event::Type Type;

            InitCollisionEngineEvent(irr::scene::ISceneManager* manager, Graphics::Render::SceneData* data):
                Event::Event(Type),
                manager_(manager),
                data_(data)
                {}

            irr::scene::ISceneManager* getManager() const
            {
                return manager_;
            }

            Graphics::Render::SceneData* getData() const
            {
                return data_;
            }

        private:
            irr::scene::ISceneManager* manager_;
            Graphics::Render::SceneData* data_;
    };
}

#endif // PHYSICS_INITCOLLISIONENGINEEVENT_H
