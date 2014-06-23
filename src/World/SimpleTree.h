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
            float truncHeight,
            float truncWidth,
            float leavesHeight,
            float leavesWidth,
            float offset,
            const Graphics::Color& truncColor,
            const Graphics::Color& leavesColor
        ):
            truncHeight_(truncHeight),
            leavesHeight_(leavesHeight),
            truncWidth_(truncWidth),
            leavesWidth_(leavesWidth),
            offset_(offset),
            truncColor_(truncColor),
            leavesColor_(leavesColor)
        {
            updateModel();
        }

        SimpleTree(const SimpleTree& tree):
            truncHeight_(tree.truncHeight_),
            leavesHeight_(tree.leavesHeight_),
            truncWidth_(tree.truncWidth_),
            leavesWidth_(tree.leavesWidth_),
            truncColor_(tree.truncColor_),
            leavesColor_(tree.leavesColor_)
        {
        }

        virtual const Graphics::Render::Model3D& getModel() const
        {
            return model_;
        }

    private:
        float truncHeight_;
        float leavesHeight_;
        float truncWidth_;
        float leavesWidth_;
        float offset_;
        Graphics::Color truncColor_;
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
