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

#ifndef GRAPHICS_RENDER_CAMERASCENENODE_H
#define GRAPHICS_RENDER_CAMERASCENENODE_H

#include <irrlicht/ICameraSceneNode.h>

#include "SceneNode.h"

namespace Graphics
{
    namespace Render
    {
        /**
        *   Class describing the player's camera scene node
        */
        class CameraSceneNode : public SceneNode
        {
        public:
            CameraSceneNode(const SceneNode* parent);
            virtual ~CameraSceneNode();

            void setIrrlichtSceneNode(irr::scene::ICameraSceneNode* node);

            /*
            *   This method fixes the camera target at each step of the rendering loop
            */
            void updateTarget(const irr::core::position2df& cursorPos);
            /*
            *   Initialize the camera position (relative to the player's)
            */
            void initPositionAndTargetFromParent();

            void initStaticCamera(const Geometry::Vec3Df& position, const Geometry::Vec3Df& target);
        protected:
            // override
            virtual void removeIrrlichtSceneNode();
        private:
            float maxVerticalAngle_;
            float rotateSpeed_;
        };
    }
}

#endif // GRAPHICS_RENDER_CAMERASCENENODE_H
