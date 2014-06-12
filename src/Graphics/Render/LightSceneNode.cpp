#include "LightSceneNode.h"

namespace Graphics
{
    namespace Render
    {
        LightSceneNode::LightSceneNode(const SceneNode& parent):
            SceneNode(parent)
        {
        }

        LightSceneNode::~LightSceneNode()
        {
            //dtor
        }

        void LightSceneNode::setIrrlichtSceneNode(irr::scene::ILightSceneNode* node)
        {
            irrlichtSceneNode_ = dynamic_cast<irr::scene::ISceneNode*>(node);
        }

        void LightSceneNode::removeIrrlichtSceneNode()
        {
            dynamic_cast<irr::scene::ILightSceneNode*>(irrlichtSceneNode_)->remove();
        }
    }
}

