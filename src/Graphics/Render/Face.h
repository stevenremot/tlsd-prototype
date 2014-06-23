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

#ifndef GRAPHICS_RENDER_FACE_H
#define GRAPHICS_RENDER_FACE_H

#include <stdexcept>

#include "../Color.h"

namespace Graphics
{
    namespace Render
    {
        /**
         *Represent a triangle in a 3D mesh
         */
        class Face
        {
        public:
            Face(unsigned int v1, unsigned int v2, unsigned int v3, const Color& color):
                color_(color),
                vertices_(new unsigned int[3])
            {
                vertices_[0] = v1;
                vertices_[1] = v2;
                vertices_[2] = v3;
            }

            Face(const Face& face):
                color_(face.color_),
                vertices_(new unsigned int[3])
            {
                vertices_[0] = face.vertices_[0];
                vertices_[1] = face.vertices_[1];
                vertices_[2] = face.vertices_[2];
            }

            ~Face()
            {
                delete[] vertices_;
            }

            unsigned int& operator[](unsigned int i)
            {
                if (i >= 3)
                {
                    throw std::out_of_range("Looked beyond the 3 vertices.");
                }
                return vertices_[i];
            }

            unsigned int operator[](unsigned int i) const
            {
                if (i >= 3)
                {
                    throw std::out_of_range("Looked beyond the 3 vertices.");
                }
                return vertices_[i];
            }

            const Color& getColor() const
            {
                return color_;
            }

        private:
            Color color_;
            unsigned int* vertices_;
        };
    }
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
