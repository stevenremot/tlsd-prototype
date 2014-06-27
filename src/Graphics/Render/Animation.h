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
                speed_(5.0f),
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
