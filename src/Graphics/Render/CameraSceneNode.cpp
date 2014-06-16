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

#include "CameraSceneNode.h"

#include <irrlicht/SViewFrustum.h>

namespace Graphics
{
    namespace Render
    {
        using irr::core::vector3df;

        CameraSceneNode::CameraSceneNode(const SceneNode* parent) :
            SceneNode(parent)
        {
            maxVerticalAngle_ = 45.0f;
            rotateSpeed_ = 0.5f;
        }

        CameraSceneNode::~CameraSceneNode()
        {

        }

        void CameraSceneNode::removeIrrlichtSceneNode()
        {
            static_cast<irr::scene::ICameraSceneNode*>(irrlichtSceneNode_)->remove();
        }

        void CameraSceneNode::setIrrlichtSceneNode(irr::scene::ICameraSceneNode* node)
        {
            irrlichtSceneNode_ = static_cast<irr::scene::ISceneNode*>(node);
        }

        void CameraSceneNode::updateTarget(const irr::core::position2df& cursorPos)
        {
            irr::scene::ICameraSceneNode* cameraNode = static_cast<irr::scene::ICameraSceneNode*>(irrlichtSceneNode_);

            const irr::scene::SViewFrustum* frustum = cameraNode->getViewFrustum();

            vector3df farLeftUp = frustum->getFarLeftUp();
            vector3df leftToRight = frustum->getFarRightUp() - farLeftUp;
            vector3df upToDown = frustum->getFarLeftDown() - farLeftUp;

            vector3df newTarget = farLeftUp + leftToRight*cursorPos.X + upToDown*cursorPos.Y;
            // tweening
            vector3df target = newTarget*rotateSpeed_ + cameraNode->getTarget()*(1-rotateSpeed_);

            // check vertical angle
            float verticalAngle = (target - cameraNode->getAbsolutePosition()).getHorizontalAngle().X;
            if (verticalAngle > 180.0f)
                verticalAngle = 360.0f-verticalAngle;
            if (verticalAngle > maxVerticalAngle_||verticalAngle < -maxVerticalAngle_)
                return;

            cameraNode->setTarget(target);
        }

        void CameraSceneNode::initPositionAndTargetFromParent()
        {
            irr::scene::ICameraSceneNode* cameraNode = dynamic_cast<irr::scene::ICameraSceneNode*>(irrlichtSceneNode_);

            // we use the parent of the irrlichtSceneNode_ to avoid translating the position in and from Vec3Df
            irr::scene::ISceneNode* parent = irrlichtSceneNode_->getParent();
            // put the camera behind the player
            vector3df charDir = parent->getRotation().rotationToDirection(vector3df(-1,0,0));
            vector3df charScale = parent->getScale();
            vector3df charDims = parent->getBoundingBox().getExtent();
            vector3df pos = vector3df(0,charDims.Y*1.2f,0) - 2.0f * vector3df(charDims.X*charDir.X,0,charDims.Z*charDir.Z);
            cameraNode->setPosition(pos);
            cameraNode->updateAbsolutePosition();

            vector3df target = parent->getPosition() + vector3df(0,charScale.Y*charDims.Y,0);// + 0.2f * core::vector3df(charDims.X*charDir.X,0,10.0f*charDims.Z*charDir.Z);
            cameraNode->setTarget(target);
        }

        void CameraSceneNode::initStaticCamera(const Vec3Df& position, const Vec3Df& target)
        {
            setPosition(position);

            static_cast<irr::scene::ICameraSceneNode*>(irrlichtSceneNode_)->setTarget(vector3df(target.getX(), target.getZ(), target.getY()));
        }
    }
}
