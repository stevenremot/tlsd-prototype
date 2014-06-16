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
