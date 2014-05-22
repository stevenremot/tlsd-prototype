#ifndef GRAPHICS_RENDER_CAMERASCENENODE_H
#define GRAPHICS_RENDER_CAMERASCENENODE_H

#include "SceneNode.h"

namespace Graphics
{
    namespace Render
    {
        class CameraSceneNode : public SceneNode
        {
        public:
            CameraSceneNode(const SceneNode* parent);
            virtual ~CameraSceneNode();
        protected:
        private:
            float maxVerticalAngle_;
            float rotateSpeed_;
        };
    }
}

#endif // GRAPHICS_RENDER_CAMERASCENENODE_H
