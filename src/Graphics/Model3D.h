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

#ifndef GRAPHICS_MODEL3D_H
#define GRAPHICS_MODEL3D_H

#include <vector>

#include "../Geometry/Vec3D.h"
#include "Face.h"

namespace Graphics
{
    /**
     * Class describing a 3D coloured mesh
     */
    class Model3D
    {
    public:
        Model3D() {}

        Model3D(const std::vector<Geometry::Vec3Df>& vertices,
                const std::vector<Face>& faces):
            vertices_(vertices),
            faces_(faces)
        {}

        Model3D(const Model3D& model):
            vertices_(model.getVertices()),
            faces_(model.getFaces())
        {}

        std::vector<Geometry::Vec3Df>& getVertices()
        {
            return vertices_;
        }

        const std::vector<Geometry::Vec3Df>& getVertices() const
        {
            return vertices_;
        }

        std::vector<Face>& getFaces()
        {
            return faces_;
        }

        const std::vector<Face>& getFaces() const
        {
            return faces_;
        }

    private:
        std::vector<Geometry::Vec3Df> vertices_;
        std::vector<Face> faces_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
