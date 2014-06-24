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

#ifndef WORLD_GENERATION_TREE_PARAMETERS_H
#define WORLD_GENERATION_TREE_PARAMETERS_H

#include "../../Graphics/Color.h"

namespace World
{
    namespace Generation
    {
        /**
         * Contains all parameters for trees generation
         */
        class TreeParameters
        {
        public:
            TreeParameters(float minTrunkHeight, float maxTrunkHeight, float minTrunkWidth, float maxTrunkWidth, float minLeavesHeight, float maxLeavesHeight, float minLeavesWidth, float maxLeavesWidth, float minOffset, float maxOffset, Graphics::Color minTrunkColor, Graphics::Color maxTrunkColor, Graphics::Color minLeavesColor, Graphics::Color maxLeavesColor):
                minTrunkHeight_(minTrunkHeight),
                maxTrunkHeight_(maxTrunkHeight),
                minTrunkWidth_(minTrunkWidth),
                maxTrunkWidth_(maxTrunkWidth),
                minLeavesHeight_(minLeavesHeight),
                maxLeavesHeight_(maxLeavesHeight),
                minLeavesWidth_(minLeavesWidth),
                maxLeavesWidth_(maxLeavesWidth),
                minOffset_(minOffset),
                maxOffset_(maxOffset),
                minTrunkColor_(minTrunkColor),
                maxTrunkColor_(maxTrunkColor),
                minLeavesColor_(minLeavesColor),
                maxLeavesColor_(maxLeavesColor)
            {}

            float getMinTrunkHeight() const { return minTrunkHeight_; }
            void setMinTrunkHeight(float minTrunkHeight)
            {
                minTrunkHeight_ = minTrunkHeight;
            }

            float getMaxTrunkHeight() const { return maxTrunkHeight_; }
            void setMaxTrunkHeight(float maxTrunkHeight)
            {
                maxTrunkHeight_ = maxTrunkHeight;
            }

            float getMinTrunkWidth() const { return minTrunkWidth_; }
            void setMinTrunkWidth(float minTrunkWidth)
            {
                minTrunkWidth_ = minTrunkWidth;
            }

            float getMaxTrunkWidth() const { return maxTrunkWidth_; }
            void setMaxTrunkWidth(float maxTrunkWidth)
            {
                maxTrunkWidth_ = maxTrunkWidth;
            }

            float getMinLeavesHeight() const { return minLeavesHeight_; }
            void setMinLeavesHeight(float minLeavesHeight)
            {
                minLeavesHeight_ = minLeavesHeight;
            }

            float getMaxLeavesHeight() const { return maxLeavesHeight_; }
            void setMaxLeavesHeight(float maxLeavesHeight)
            {
                maxLeavesHeight_ = maxLeavesHeight;
            }

            float getMinLeavesWidth() const { return minLeavesWidth_; }
            void setMinLeavesWidth(float minLeavesWidth)
            {
                minLeavesWidth_ = minLeavesWidth;
            }

            float getMaxLeavesWidth() const { return maxLeavesWidth_; }
            void setMaxLeavesWidth(float maxLeavesWidth)
            {
                maxLeavesWidth_ = maxLeavesWidth;
            }

            float getMinOffset() const { return minOffset_; }
            void setMinOffset(float minOffset)
            {
                minOffset_ = minOffset;
            }

            float getMaxOffset() const { return maxOffset_; }
            void setMaxOffset(float maxOffset)
            {
                maxOffset_ = maxOffset;
            }

            const Graphics::Color& getMinTrunkColor() const
            {
                return minTrunkColor_;
            }
            void setMinTrunkColor(const Graphics::Color& minTrunkColor)
            {
                minTrunkColor_ = minTrunkColor;
            }

            const Graphics::Color& getMaxTrunkColor() const
            {
                return maxTrunkColor_;
            }
            void setMaxTrunkColor(const Graphics::Color& maxTrunkColor)
            {
                maxTrunkColor_ = maxTrunkColor;
            }

            const Graphics::Color& getMinLeavesColor() const
            {
                return minLeavesColor_;
            }
            void setMinLeavesColor(const Graphics::Color& minLeavesColor)
            {
                minLeavesColor_ = minLeavesColor;
            }

            const Graphics::Color& getMaxLeavesColor() const
            {
                return maxLeavesColor_;
            }
            void setMaxLeavesColor(const Graphics::Color& maxLeavesColor)
            {
                maxLeavesColor_ = maxLeavesColor;
            }

        private:
            float minTrunkHeight_;
            float maxTrunkHeight_;
            float minTrunkWidth_;
            float maxTrunkWidth_;
            float minLeavesHeight_;
            float maxLeavesHeight_;
            float minLeavesWidth_;
            float maxLeavesWidth_;
            float minOffset_;
            float maxOffset_;
            Graphics::Color minTrunkColor_;
            Graphics::Color maxTrunkColor_;
            Graphics::Color minLeavesColor_;
            Graphics::Color maxLeavesColor_;
        };
    }
}

#endif
