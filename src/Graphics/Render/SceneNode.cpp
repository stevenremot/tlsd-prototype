#include "SceneNode.h"

#include <irrlicht/matrix4.h>

namespace Graphics
{
    namespace Render
    {
        using irr::core::vector3df;
        using irr::core::matrix4;

        SceneNode::SceneNode(const SceneNode* parent) :
            parent_(parent),
            irrlichtSceneNode_(NULL)
        {
            //ctor
        }

        SceneNode::~SceneNode()
        {
            // delete all the node's children
            for(std::list<SceneNode*>::iterator it = children_.begin(); it != children_.end(); ++it)
                delete *it;

            // inherited classes have their own type of irrlicht scene node
            removeIrrlichtSceneNode();
        }

        void SceneNode::removeIrrlichtSceneNode()
        {
            if (irrlichtSceneNode_ != NULL)
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

        Vec3Df SceneNode::getAbsolutePosition() const
        {
            vector3df irrPos = irrlichtSceneNode_->getAbsolutePosition();
            return Vec3Df(irrPos.X, irrPos.Z, irrPos.Y);
        }

        Vec3Df SceneNode::getAbsoluteRotation() const
        {
            if (getParent()->getId() == 0)
                return getRotation();
            else
            {
                vector3df irrRot = irrlichtSceneNode_->getAbsoluteTransformation().getRotationDegrees();
                return Vec3Df(irrRot.X, irrRot.Z, irrRot.Y);
            }
        }

        void SceneNode::setPosition(const Vec3Df& pos)
        {
            vector3df irrPos = vector3df(pos.getX(), pos.getZ(), pos.getY());
            irrlichtSceneNode_->setPosition(irrPos);
        }


        void SceneNode::setRotation(const Vec3Df& rot)
        {
            vector3df irrRot = vector3df(rot.getX(), rot.getZ(), rot.getY());
            irrlichtSceneNode_->setRotation(irrRot);
        }


        void SceneNode::setScale(const Vec3Df& sca)
        {
            vector3df irrScale = vector3df(sca.getX(), sca.getZ(), sca.getY());
            irrlichtSceneNode_->setScale(irrScale);
        }

        void SceneNode::setAbsolutePosition(const Vec3Df& pos)
        {
            vector3df irrPos = vector3df(pos.getX(), pos.getZ(), pos.getY());

            if(getParent() != NULL)
            {
                // The parent is not the root scene node
                if (getParent()->getId() != 0)
                {
                    // the transform matrix is initialized at identity
                    matrix4 matr;
                    matr.setTranslation(irrPos);

                    const matrix4 w2n(irrlichtSceneNode_->getParent()->getAbsoluteTransformation(), irr::core::matrix4::EM4CONST_INVERSE);

                    matr = (w2n*matr);

                    irrlichtSceneNode_->setPosition(matr.getTranslation());
                    irrlichtSceneNode_->setRotation(matr.getRotationDegrees());
                    irrlichtSceneNode_->updateAbsolutePosition();
                }
                else
                    setPosition(pos);
            }
        }

        void SceneNode::setAbsoluteRotation(const Vec3Df& rot)
        {
            vector3df irrRot = vector3df(rot.getX(), rot.getZ(), rot.getY());

            if(getParent() != NULL)
            {
                // The parent is not the root scene node
                if (getParent()->getId() != 0)
                {
                    // the transform matrix is initialized at identity
                    matrix4 matr;
                    matr.setRotationDegrees(irrRot);

                    const matrix4 w2n(irrlichtSceneNode_->getParent()->getAbsoluteTransformation(), irr::core::matrix4::EM4CONST_INVERSE);

                    matr = (w2n*matr);

                    irrlichtSceneNode_->setPosition(matr.getTranslation());
                    irrlichtSceneNode_->setRotation(matr.getRotationDegrees());
                    irrlichtSceneNode_->updateAbsolutePosition();
                }
                else
                    setRotation(rot);
            }
        }

        void SceneNode::setId(unsigned int id)
        {
            id_ = id;
            irrlichtSceneNode_->setID(id_);
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

        irr::scene::ISceneNode* SceneNode::getIrrlichtSceneNode() const
        {
            return irrlichtSceneNode_;
        }

        void SceneNode::setIrrlichtSceneNode(irr::scene::ISceneNode* node)
        {
            irrlichtSceneNode_ = node;
        }

        void SceneNode::activateLight(bool b)
        {
            irrlichtSceneNode_->setMaterialFlag(irr::video::EMF_LIGHTING, b);
        }

        void SceneNode::setFlatShading(bool b)
        {
            irrlichtSceneNode_->setMaterialFlag(irr::video::EMF_GOURAUD_SHADING, !b);
        }

        void SceneNode::addChild(SceneNode* child)
        {
            children_.push_back(child);
        }
    }
}