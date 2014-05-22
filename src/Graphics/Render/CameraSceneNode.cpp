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
            irrlichtSceneNode_->remove();
        }

        Vec3Df CameraSceneNode::getPosition() const
        {
            vector3df irrPosition = irrlichtSceneNode_->getPosition();
            return Vec3Df(irrPosition.X, irrPosition.Z, irrPosition.Y);
        }

        Vec3Df CameraSceneNode::getRotation() const
        {
            vector3df irrRotation = irrlichtSceneNode_->getRotation();
            return Vec3Df(irrRotation.X, irrRotation.Z, irrRotation.Y);
        }

        Vec3Df CameraSceneNode::getScale() const
        {
            vector3df irrScale = irrlichtSceneNode_->getScale();
            return Vec3Df(irrScale.X, irrScale.Z, irrScale.Y);
        }

        void CameraSceneNode::setIrrlichtSceneNode(irr::scene::ICameraSceneNode* node)
        {
            irrlichtSceneNode_ = node;
        }

        void CameraSceneNode::updateTarget(irr::core::position2df cursorPos)
        {
            const irr::scene::SViewFrustum* frustum = irrlichtSceneNode_->getViewFrustum();

            vector3df farLeftUp = frustum->getFarLeftUp();
            vector3df leftToRight = frustum->getFarRightUp() - farLeftUp;
            vector3df upToDown = frustum->getFarLeftDown() - farLeftUp;

            vector3df newTarget = farLeftUp + leftToRight*cursorPos.X + upToDown*cursorPos.Y;
            // tweening
            vector3df target = newTarget*rotateSpeed_ + irrlichtSceneNode_->getTarget()*(1-rotateSpeed_);

            // check vertical angle
            float verticalAngle = (target - irrlichtSceneNode_->getAbsolutePosition()).getHorizontalAngle().X;
            if (verticalAngle > 180.0f)
                verticalAngle = 360.0f-verticalAngle;
            if (verticalAngle > maxVerticalAngle_||verticalAngle < -maxVerticalAngle_)
                return;

            irrlichtSceneNode_->setTarget(target);
        }

        void CameraSceneNode::initPositionAndTarget()
        {
            // we use the parent of the irrlichtSceneNode_ to avoid translating the position in and from Vec3Df
            irr::scene::ISceneNode* parent = irrlichtSceneNode_->getParent();
            // put the camera behind the player
            vector3df charDir = parent->getRotation().rotationToDirection();
            vector3df charScale = parent->getScale();
            vector3df charDims = parent->getBoundingBox().getExtent();
            vector3df pos = vector3df(0,charDims.Y,0) - 2.0f * vector3df(charDims.X*charDir.X,0,charDims.Z*charDir.Z);
            irrlichtSceneNode_->setPosition(pos);
            irrlichtSceneNode_->updateAbsolutePosition();

            vector3df target = parent->getPosition() + vector3df(0,charScale.Y*charDims.Y,0);// + 0.2f * core::vector3df(charDims.X*charDir.X,0,10.0f*charDims.Z*charDir.Z);
            irrlichtSceneNode_->setTarget(target);
        }
    }
}
