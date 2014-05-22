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

            // overrides
            virtual Vec3Df getPosition() const;
            virtual Vec3Df getRotation() const;
            virtual Vec3Df getScale() const;

            void setIrrlichtSceneNode(irr::scene::ICameraSceneNode* node);

            /*
            *   This method fixes the camera target at each step of the rendering loop
            */
            void updateTarget(irr::core::position2df cursorPos);
            /*
            *   Initialize the camera position (relative to the player's)
            */
            void initPositionAndTarget();
        protected:
        private:
            float maxVerticalAngle_;
            float rotateSpeed_;
            irr::scene::ICameraSceneNode* irrlichtSceneNode_;
        };
    }
}

#endif // GRAPHICS_RENDER_CAMERASCENENODE_H
