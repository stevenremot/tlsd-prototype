#ifndef GRAPHICS_RENDER_LIGHTSCENENODE_H
#define GRAPHICS_RENDER_LIGHTSCENENODE_H

#include "SceneNode.h"
#include <irrlicht/ILightSceneNode.h>

namespace Graphics
{
    namespace Render
    {
        class LightSceneNode : public SceneNode
        {
        public:
            LightSceneNode(const SceneNode& parent);
            virtual ~LightSceneNode();

            void setIrrlichtSceneNode(irr::scene::ILightSceneNode* node);
        protected:
            // override
            virtual void removeIrrlichtSceneNode();
        private:
        };
    }
}

#endif // GRAPHICS_RENDER_LIGHTSCENENODE_H
