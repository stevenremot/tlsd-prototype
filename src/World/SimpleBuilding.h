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

#ifndef WORLD_SIMPLE_BUILDING_H
#define WORLD_SIMPLE_BUILDING_H

#include "BuildingInterface.h"

#include "../Geometry/Polygon2D.h"
#include "../Graphics/Color.h"

namespace World
{
    class SimpleBuilding: public BuildingInterface
    {
    public:
        SimpleBuilding(
            const Geometry::Polygon2D& base,
            float wallHeight,
            float roofHeight,
            const Graphics::Color& wallColor,
            const Graphics::Color& roofColor
        ):
            base_(base),
            wallHeight_(wallHeight),
            roofHeight_(roofHeight),
            wallColor_(wallColor),
            roofColor_(roofColor)
        {
            updateModel();
        }

        SimpleBuilding(const SimpleBuilding& building):
            base_(building.base_),
            wallHeight_(building.wallHeight_),
            roofHeight_(building.roofHeight_),
            wallColor_(building.wallColor_),
            roofColor_(building.roofColor_),
            model_(building.model_)
        {
        }

        virtual const Graphics::Render::Model3D& getModel() const
        {
            return model_;
        }

    private:
        Geometry::Polygon2D base_;
        float wallHeight_;
        float roofHeight_;
        Graphics::Color wallColor_;
        Graphics::Color roofColor_;

        Graphics::Render::Model3D model_;

        void updateModel();
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
