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

#include "PerlinNoise.h"

using Geometry::Vec2Di;
using Geometry::Vec2Df;

namespace Random
{
    PerlinNoise::PerlinNoise(): coefficients_()
    {}

    PerlinNoise& PerlinNoise::setCoefficient(
        const Geometry::Vec2Di& position,
        const Geometry::Vec2Df& coefficient
    ) {
        coefficients_[position] = coefficient;
        return *this;
    }

    float PerlinNoise::computeAt(const Geometry::Vec2Df& position) const
    {
        int i = floor(position.getX());
        int j = floor(position.getY());

        float x0 = position.getX() - i;
        float y0 = position.getY() - j;

        float n00, n01, n10, n11;
        try
        {
            n00 = coefficients_.at(Vec2Di(i, j)).dot(Vec2Df(x0, y0));
            n10 = coefficients_.at(Vec2Di(i + 1, j)).dot(Vec2Df(x0 - 1, y0));
            n01 = coefficients_.at(Vec2Di(i, j + 1)).dot(Vec2Df(x0, y0 - 1));
            n11 = coefficients_.at(Vec2Di(i + 1, j + 1)).dot(Vec2Df(x0 - 1, y0 - 1));

        }
        catch (const std::out_of_range& e)
        {
            throw UninitializedCoefficientsException();
        }

        float interpolantX = x0 * x0 * x0 * (x0 * (x0 * 6 - 15) + 10);
        float interpolantY = y0 * y0 * y0 * (y0 * (y0 * 6 - 15) + 10);

        float nx0 = n00 * (1 - interpolantX) + n10 * interpolantX;
        float nx1 = n01 * (1 - interpolantX) + n11 * interpolantX;
        return nx0 * (1 - interpolantY) + nx1 * interpolantY;
    }
}
