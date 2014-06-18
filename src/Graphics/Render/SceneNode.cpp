/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#include "SceneNode.h"
#include "../../Geometry/IrrlichtConversions.h"

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
            return Geometry::fromIrrVector3df(irrPosition);
        }

        Vec3Df SceneNode::getRotation() const
        {
            vector3df irrRotation = irrlichtSceneNode_->getRotation();
            return Geometry::fromIrrVector3df(irrRotation);
        }

        Vec3Df SceneNode::getScale() const
        {
            vector3df irrScale = irrlichtSceneNode_->getScale();
            return Geometry::fromIrrVector3df(irrScale);
        }

        Vec3Df SceneNode::getAbsolutePosition() const
        {
            vector3df irrPos = irrlichtSceneNode_->getAbsolutePosition();
            return Geometry::fromIrrVector3df(irrPos);
        }

        Vec3Df SceneNode::getAbsoluteRotation() const
        {
            if (getParent()->getId() == 0)
                return getRotation();
            else
            {
                vector3df irrRot = irrlichtSceneNode_->getAbsoluteTransformation().getRotationDegrees();
                return Geometry::fromIrrVector3df(irrRot);
            }
        }

        void SceneNode::setPosition(const Vec3Df& pos)
        {
            vector3df irrPos = Geometry::fromVec3Df(pos);
            irrlichtSceneNode_->setPosition(irrPos);
        }


        void SceneNode::setRotation(const Vec3Df& rot)
        {
            vector3df irrRot = Geometry::fromVec3Df(rot);
            irrlichtSceneNode_->setRotation(irrRot);
        }


        void SceneNode::setScale(const Vec3Df& sca)
        {
            vector3df irrScale = Geometry::fromVec3Df(sca);
            irrlichtSceneNode_->setScale(irrScale);
        }

        void SceneNode::setAbsolutePosition(const Vec3Df& pos)
        {
            vector3df irrPos = Geometry::fromVec3Df(pos);

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
            vector3df irrRot = Geometry::fromVec3Df(rot);

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

        unsigned int SceneNode::getId() const
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
