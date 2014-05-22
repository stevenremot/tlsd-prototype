#include "SceneNode.h"

namespace Graphics
{
    namespace Render
    {
        using irr::core::vector3df;

        SceneNode::SceneNode(const SceneNode* parent) :
            parent_(parent)
        {
            //ctor
        }

        SceneNode::~SceneNode()
        {
            // delete all the node's children
            for(std::list<SceneNode*>::iterator it = children_.begin(); it != children_.end(); ++it)
                delete *it;

            irrlichtSceneNode_->remove();
        }

        Vec3Df SceneNode::getPosition() const
        {
            vector3df irrPosition = irrlichtSceneNode_->getPosition();
            return Vec3Df(irrPosition.X, irrPosition.Z, irrPosition.Y);
        }

        Vec3Df SceneNode::getRotation() const
        {
            vector3df irrRotation = irrlichtSceneNode_->getRotation();
            return Vec3Df(irrRotation.X, irrRotation.Z, irrRotation.Y);
        }

        Vec3Df SceneNode::getScale() const
        {
            vector3df irrScale = irrlichtSceneNode_->getScale();
            return Vec3Df(irrScale.X, irrScale.Z, irrScale.Y);
        }

        const unsigned int SceneNode::getId() const
        {
            return id_;
        }

        const SceneNode* SceneNode::getParent() const
        {
            return parent_;
        }

        const std::list<SceneNode*>& SceneNode::getChildren() const
        {
            return children_;
        }

        void SceneNode::setIrrlichtSceneNode(irr::scene::ISceneNode* node)
        {
            irrlichtSceneNode_ = node;
        }
    }
}
