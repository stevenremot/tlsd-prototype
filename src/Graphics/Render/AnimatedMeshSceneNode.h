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
