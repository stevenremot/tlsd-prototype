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

#ifndef GRAPHICS_RENDER_ANIMATEDMESHSCENENODE_H
#define GRAPHICS_RENDER_ANIMATEDMESHSCENENODE_H

#include <exception>
#include <vector>
#include <irrlicht/IAnimatedMeshSceneNode.h>

#include "MeshSceneNode.h"
#include "Animation.h"

using std::vector;

namespace Graphics
{
    namespace Render
    {
        class NotSupportedAnimationException: public std::exception
        {
            const char* what() const throw()
            {
                return "This animation is not supported by this animated mesh.";
            }
        };

        class AnimatedMeshSceneNode : public MeshSceneNode, public irr::scene::IAnimationEndCallBack
        {
        public:
            AnimatedMeshSceneNode(const SceneNode& parent);
            virtual ~AnimatedMeshSceneNode();

            void applyAnimation(const AnimationType& animation);

            void update();

            // hardcoded for the ninja animation
            // TODO: replace by a more flexible implementation
            bool getAnimationFrames(const AnimationType& animation, unsigned int& start, unsigned int& end);

            // IAnimationEndCallback override
            virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);

            void setAnimationMap(const AnimationMap& animationMap);
            void setIrrlichtSceneNode(irr::scene::IAnimatedMeshSceneNode* node);

        protected:
            // SceneNode override
            virtual void removeIrrlichtSceneNode();

        private:
            AnimationMap animationMap_;
            AnimationType currentAnimation_;
            float transitionTime_;
            unsigned int framesWithoutAnimationOrder_;
        };
    }
}

#endif // GRAPHICS_RENDER_ANIMATEDMESHSCENENODE_H
