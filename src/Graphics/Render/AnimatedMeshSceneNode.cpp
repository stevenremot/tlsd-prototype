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

#include "AnimatedMeshSceneNode.h"

#include <iostream>

namespace Graphics
{
    namespace Render
    {
        AnimatedMeshSceneNode::AnimatedMeshSceneNode(const SceneNode& parent):
            MeshSceneNode(parent),
            currentAnimation_(NoAnimation),
            transitionTime_(0.5),
            framesWithoutAnimationOrder_(0)
        {
            //ctor
        }

        AnimatedMeshSceneNode::~AnimatedMeshSceneNode()
        {
            //dtor
        }

        void AnimatedMeshSceneNode::removeIrrlichtSceneNode()
        {
            dynamic_cast<irr::scene::IAnimatedMeshSceneNode*>(irrlichtSceneNode_)->remove();
        }

        void AnimatedMeshSceneNode::setAnimationMap(const AnimationMap& animationMap)
        {
            animationMap_ = animationMap;
            applyAnimation(Idle);
        }

        void AnimatedMeshSceneNode::setIrrlichtSceneNode(irr::scene::IAnimatedMeshSceneNode* node)
        {
            irrlichtSceneNode_ = dynamic_cast<irr::scene::ISceneNode*>(node);

            node->setJointMode(irr::scene::EJUOR_CONTROL);
            node->setTransitionTime(transitionTime_);
        }

        void AnimatedMeshSceneNode::applyAnimation(const AnimationType& animation)
        {
/*            if (currentAnimation_ == animation)
            {
                framesWithoutAnimationOrder_ = 0;
            }
*/
            if (currentAnimation_ == NoAnimation ||
                (currentAnimation_ != animation && animationMap_[currentAnimation_].getOnEndCallback() == NoAnimation))
            {
                currentAnimation_ = animation;
                unsigned int start = 0, end = 0;

                if (!getAnimationFrames(animation, start, end))
                    throw new NotSupportedAnimationException();

                irr::scene::IAnimatedMeshSceneNode* animatedNode = dynamic_cast<irr::scene::IAnimatedMeshSceneNode*>(irrlichtSceneNode_);

                animatedNode->setAnimationSpeed(animationMap_[animation].getSpeed());
                animatedNode->setLoopMode(animationMap_[animation].getLoop());
                animatedNode->setFrameLoop(start, end);
                if (animationMap_[animation].getOnEndCallback() != NoAnimation)
                    animatedNode->setAnimationEndCallback(this);

                framesWithoutAnimationOrder_ = 0;
            }
        }

        bool AnimatedMeshSceneNode::getAnimationFrames(const AnimationType& animation, unsigned int& start, unsigned int& end)
        {
            switch (animation)
            {
            case Attack:
                start = 60;
                end = 68;
                return true;
            case Idle:
                start = 206;
                end = 300;
                return true;
            case Walk:
                start = 0;
                end = 13;
                return true;
            case Magic:
                start = 69;
                end = 72;
                return true;
            default:
                return false;
            }
        }

        void AnimatedMeshSceneNode::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node)
        {
            applyAnimation(animationMap_[currentAnimation_].getOnEndCallback());
        }

        void AnimatedMeshSceneNode::update()
        {
            dynamic_cast<irr::scene::IAnimatedMeshSceneNode*>(irrlichtSceneNode_)->animateJoints();
            /*
            framesWithoutAnimationOrder_++;

            if (framesWithoutAnimationOrder_ > 10)
                applyAnimation(Idle);
            */
        }

    }
}
