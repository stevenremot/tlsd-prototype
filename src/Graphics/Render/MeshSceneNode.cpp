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
            irrlichtSceneNode_->remove();
        }

        Vec3Df MeshSceneNode::getPosition() const
        {
            vector3df irrPosition = irrlichtSceneNode_->getPosition();
            return Vec3Df(irrPosition.X, irrPosition.Z, irrPosition.Y);
        }

        Vec3Df MeshSceneNode::getRotation() const
        {
            vector3df irrRotation = irrlichtSceneNode_->getRotation();
            return Vec3Df(irrRotation.X, irrRotation.Z, irrRotation.Y);
        }

        Vec3Df MeshSceneNode::getScale() const
        {
            vector3df irrScale = irrlichtSceneNode_->getScale();
            return Vec3Df(irrScale.X, irrScale.Z, irrScale.Y);
        }

        void MeshSceneNode::setIrrlichtSceneNode(irr::scene::IMeshSceneNode* node)
        {
            irrlichtSceneNode_ = node;
        }
    }
}
