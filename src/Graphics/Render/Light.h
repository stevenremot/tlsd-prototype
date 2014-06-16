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

#ifndef GRAPHICS_RENDER_LIGHT_H
#define GRAPHICS_RENDER_LIGHT_H

#include "../Color.h"

namespace Graphics
{
    namespace Render
    {
        enum LightType {Point, Spot, Directional};

        class Light
        {
        public:
            Light(const LightType& type, float radius, const Color& color):
                type_(type),
                radius_(radius),
                color_(color)
                {}

            const LightType& getType()
            {
                return type_;
            }

            float getRadius()
            {
                return radius_;
            }

            const Color& getColor()
            {
                return color_;
            }

        private:
            LightType type_;
            float radius_;
            Color color_;
        };
    }
}

#endif // GRAPHICS_RENDER_LIGHT_H
