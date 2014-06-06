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

            void initStaticCamera(const Vec3Df& position, const Vec3Df& target);
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
