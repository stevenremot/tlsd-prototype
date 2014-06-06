#include "MeshSceneNode.h"

namespace Graphics
{
    namespace Render
    {
        using irr::core::vector3df;

        MeshSceneNode::MeshSceneNode(const SceneNode& parent) :
            SceneNode(parent)
        {
            //ctor
        }

        MeshSceneNode::~MeshSceneNode()
        {

        }

        void MeshSceneNode::removeIrrlichtSceneNode()
        {
            dynamic_cast<irr::scene::IMeshSceneNode*>(irrlichtSceneNode_)->remove();
        }

        void MeshSceneNode::setIrrlichtSceneNode(irr::scene::IMeshSceneNode* node)
        {
            irrlichtSceneNode_ = dynamic_cast<irr::scene::ISceneNode*>(node);
        }
    }
}
