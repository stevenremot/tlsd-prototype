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

#include "ChunkGenerationListener.h"
#include "../World.h"

namespace World
{
    namespace Generation
    {
        void ChunkGenerationListener::call(const Event::Event& event)
        {
            const Input::PlayerPositionChangedEvent& evt =
                static_cast<const Input::PlayerPositionChangedEvent&>(event);

            const Geometry::Vec3Df& newPos = evt.getPosition();
            const Geometry::Vec2Di& new2DPos = Geometry::Vec2Di(
                newPos.getX() / World::ChunkSize,
                newPos.getY() / World::ChunkSize
            );

            if (new2DPos != lastPos_)
            {
                commandQueue_ << new2DPos;
                lastPos_ = new2DPos;
            }
        }
    }
}
