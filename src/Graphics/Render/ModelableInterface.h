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

#ifndef GRAPHICS_MODELABLE_INTERFACE_H
#define GRAPHICS_MODELABLE_INTERFACE_H

#include "Model3D.h"

namespace Graphics
{
    namespace Render
    {
        /**
         * Interface for objects that can be represented by a 3D model
         */
        class ModelableInterface
        {
        public:
            virtual ~ModelableInterface() {}
            virtual const Model3D& getModel() const = 0;
        };
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
