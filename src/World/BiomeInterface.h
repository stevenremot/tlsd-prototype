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

#ifndef WORLD_BIOME_INTERFACE_H
#define WORLD_BIOME_INTERFACE_H

#include "../Graphics/Color.h"

namespace World
{
    /**
     * Interface for a biome
     *
     * A biome has a transformation for the ground coefficients and a color
     *
     * TODO Rethink
     */
    class BiomeInterface
    {
    public:
        /**
         * Return the transformed base-coefficient (transformation specific for a biome)
         *
         */
        virtual float transformCoefficient(float coefficient) = 0;
        /**
         * Return the principal color of a biome
         *
         */
        virtual Graphics::Color getColor() =0;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
