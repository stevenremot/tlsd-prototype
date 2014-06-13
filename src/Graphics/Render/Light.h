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
