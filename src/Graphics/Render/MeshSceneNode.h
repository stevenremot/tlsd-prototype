#ifndef GRAPHICS_RENDER_MESHSCENENODE_H
#define GRAPHICS_RENDER_MESHSCENENODE_H

// TODO : remove when we have a proper filesystem management
#include <string>
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

            // TODO : change std::string for our proper filesystem
            bool initFromModelFile(const std::string& filename);
        protected:
            // override
            virtual void removeIrrlichtSceneNode();
        private:

        };
    }
}

#endif // GRAPHICS_RENDER_MESHSCENENODE_H
