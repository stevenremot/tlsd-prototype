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

#ifndef WORLD_GENERATION_CITY_GENERATION_PARAMETERS_H
#define WORLD_GENERATION_CITY_GENERATION_PARAMETERS_H

#include "../../../Graphics/Color.h"

namespace World
{
    namespace Generation
    {
        namespace City
        {
            /**
             * Contains all parameters for the city generation
             */
            class GenerationParameters
            {
            public:
                GenerationParameters():
                    roadLength_(45),
                    roadWidth_(2),
                    roadDeviation_(0.25),
                    expansionNumber_(100),
                    minRoadLength_(5),
                    maxRoadLength_(15),
                    minBuildingHeight_(4.0),
                    maxBuildingHeight_(20.0),
                    roadColor_(0.3, 0.3, 0.3),
                    wallColorMin_(0.8, 0.8, 0.8),
                    wallColorMax_(1.0, 1.0, 0.8),
                    roofColorMin_(0.8, 0.2, 0.2),
                    roofColorMax_(0.6, 0.1, 0.1)
                {}

                float getRoadLength() const { return roadLength_; }
                void setRoadLength(float roadLength) { roadLength_ = roadLength; }


                float getRoadWidth() const { return roadWidth_; }
                void setRoadWidth(float roadWidth) { roadWidth_ = roadWidth; }


                float getRoadDeviation() const { return roadDeviation_; }
                void setRoadDeviation(float roadDeviation)
                {
                    roadDeviation_ = roadDeviation;
                }

                unsigned int getExpansionNumber() const { return expansionNumber_; }
                void setExpansionNumber(unsigned int expansionNumber)
                {
                    expansionNumber_ = expansionNumber;
                }

                float getMinRoadLength() const { return minRoadLength_; }
                void setMinRoadLength(float minRoadLength)
                {
                    minRoadLength_ = minRoadLength;
                }

                float getMaxRoadLength() const { return maxRoadLength_; }
                void setMaxRoadLength(float maxRoadLength)
                {
                    maxRoadLength_ = maxRoadLength;
                }

                float getMinBuildingHeight() const { return minBuildingHeight_; }
                void setMinBuildingHeight(float minBuildingHeight)
                {
                    minBuildingHeight_ = minBuildingHeight;
                }

                float getMaxBuildingHeight() const { return maxBuildingHeight_; }
                void setMaxBuildingHeight(float maxBuildingHeight)
                {
                    maxBuildingHeight_ = maxBuildingHeight;
                }

                const Graphics::Color& getRoadColor() const
                {
                    return roadColor_;
                }
                void setRoadColor(const Graphics::Color& roadColor)
                {
                    roadColor_ = roadColor;
                }

                const Graphics::Color& getWallColorMin() const
                {
                    return wallColorMin_;
                }
                void setWallColorMin(const Graphics::Color& wallColorMin)
                {
                    wallColorMin_ = wallColorMin;
                }

                const Graphics::Color& getWallColorMax() const
                {
                    return wallColorMax_;
                }
                void setWallColorMax(const Graphics::Color& wallColorMax)
                {
                    wallColorMax_ = wallColorMax;
                }

                const Graphics::Color& getRoofColorMin() const
                {
                    return roofColorMin_;
                }
                void setRoofColorMin(const Graphics::Color& roofColorMin)
                {
                    roofColorMin_ = roofColorMin;
                }

                const Graphics::Color& getRoofColorMax() const
                {
                    return roofColorMax_;
                }
                void setRoofColorMax(const Graphics::Color& roofColorMax)
                {
                    roofColorMax_ = roofColorMax;
                }

            private:
                float roadLength_;
                float roadWidth_;
                float roadDeviation_;
                unsigned int expansionNumber_;
                float minRoadLength_;
                float maxRoadLength_;

                float minBuildingHeight_;
                float maxBuildingHeight_;

                Graphics::Color roadColor_;
                Graphics::Color wallColorMin_;
                Graphics::Color wallColorMax_;
                Graphics::Color roofColorMin_;
                Graphics::Color roofColorMax_;
            };
        }
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
