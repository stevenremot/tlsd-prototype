#include "CameraSceneNode.h"

namespace Graphics
{
    namespace Render
    {
        CameraSceneNode::CameraSceneNode(const SceneNode* parent) :
            SceneNode(parent)
        {
            maxVerticalAngle_ = 45.0f;
            rotateSpeed_ = 0.5f;
        }

        CameraSceneNode::~CameraSceneNode()
        {
            //dtor
        }
    }
}
