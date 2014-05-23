#ifndef GRAPHICS_RENDER_MESHSCENENODE_H
#define GRAPHICS_RENDER_MESHSCENENODE_H

#include <irrlicht/IMeshSceneNode.h>

#include "SceneNode.h"
#include "Model3D.h"

namespace Graphics
{
    namespace Render
    {
        class MeshSceneNode : public SceneNode
        {
        public:
            MeshSceneNode(const SceneNode& parent);
            virtual ~MeshSceneNode();

            void setIrrlichtSceneNode(irr::scene::IMeshSceneNode* node);

            void initFromModel3D(const Model3D& model);
        protected:
            // override
            virtual void removeIrrlichtSceneNode();
        private:

        };
    }
}

#endif // GRAPHICS_RENDER_MESHSCENENODE_H
