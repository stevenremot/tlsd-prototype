#ifndef GRAPHICS_RENDER_ANIMATION_H
#define GRAPHICS_RENDER_ANIMATION_H

#include <map>

namespace Graphics
{
    namespace Render
    {
        enum AnimationType {NoAnimation, Idle, Walk, Strafe, Jump, Attack, Magic};

        class AnimationParameters
        {
        public:
            AnimationParameters():
                speed_(1.0f),
                loop_(false),
                onEndCallback_(NoAnimation)
                {}

            AnimationParameters(float speed, bool loop, AnimationType onEndCallback):
                speed_(speed),
                loop_(loop),
                onEndCallback_(onEndCallback)
                {}

            float getSpeed()
            {
                return speed_;
            }

            bool getLoop()
            {
                return loop_;
            }

            const AnimationType& getOnEndCallback()
            {
                return onEndCallback_;
            }

        private:
            float speed_;
            bool loop_;
            AnimationType onEndCallback_;
        };

        typedef std::map<AnimationType, AnimationParameters> AnimationMap;
    }
}

#endif // GRAPHICS_RENDER_ANIMATION_H
