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

#ifndef WORLD_SIMPLE_TREE_H
#define WORLD_SIMPLE_TREE_H

#include "TreeInterface.h"

#include "../Graphics/Color.h"
#include "../Geometry/Vec2D.h"
#include "../Geometry/Vec3D.h"

namespace World
{
    class SimpleTree: public TreeInterface
    {
    public:
        SimpleTree(
            float trunkHeight,
            float trunkWidth,
            float leavesHeight,
            float leavesWidth,
            float offset,
            const Graphics::Color& trunkColor,
            const Graphics::Color& leavesColor
        ):
            trunkHeight_(trunkHeight),
            leavesHeight_(leavesHeight),
            trunkWidth_(trunkWidth),
            leavesWidth_(leavesWidth),
            offset_(offset),
            trunkColor_(trunkColor),
            leavesColor_(leavesColor)
        {
            updateModel();
        }

        SimpleTree(const SimpleTree& tree):
            trunkHeight_(tree.trunkHeight_),
            leavesHeight_(tree.leavesHeight_),
            trunkWidth_(tree.trunkWidth_),
            leavesWidth_(tree.leavesWidth_),
            trunkColor_(tree.trunkColor_),
            leavesColor_(tree.leavesColor_)
        {
        }

        virtual const Graphics::Render::Model3D& getModel() const
        {
            return model_;
        }

    private:
        float trunkHeight_;
        float leavesHeight_;
        float trunkWidth_;
        float leavesWidth_;
        float offset_;
        Graphics::Color trunkColor_;
        Graphics::Color leavesColor_;

        Graphics::Render::Model3D model_;

        void updateModel();
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
