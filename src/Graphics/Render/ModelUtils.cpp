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

#include "ModelUtils.h"

namespace Graphics
{
    namespace Render
    {
        using Geometry::Vec3Df;

        Model3D createCubeModel(const Color& color)
        {
            std::vector<Vec3Df> vertices;
            std::vector<Face> faces;

            vertices.push_back(Vec3Df(0.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 0.0f));
            vertices.push_back(Vec3Df(0.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 1.0f));

            faces.push_back(Face(0,2,1,color));
            faces.push_back(Face(0,1,3,color));

            faces.push_back(Face(0,3,2,color));
            faces.push_back(Face(1,2,4,color));

            faces.push_back(Face(2,3,6,color));
            faces.push_back(Face(1,5,3,color));

            faces.push_back(Face(1,4,5,color));
            faces.push_back(Face(5,4,7,color));

            faces.push_back(Face(2,6,7,color));
            faces.push_back(Face(5,7,6,color));

            faces.push_back(Face(2,7,4,color));
            faces.push_back(Face(6,3,5,color));

            return Model3D(vertices, faces);
        }

        Model3D createPrettyCubeModel()
        {
            std::vector<Vec3Df> vertices;
            std::vector<Face> faces;

            vertices.push_back(Vec3Df(0.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 0.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 0.0f));

            vertices.push_back(Vec3Df(1.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 0.0f));

            vertices.push_back(Vec3Df(1.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(0.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 1.0f));

            vertices.push_back(Vec3Df(0.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(0.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 0.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 1.0f));

            vertices.push_back(Vec3Df(0.0f, 1.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 0.0f));
            vertices.push_back(Vec3Df(1.0f, 1.0f, 1.0f));
            vertices.push_back(Vec3Df(0.0f, 1.0f, 1.0f));

            vertices.push_back(Vec3Df(0.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 0.0f, 1.0f));
            vertices.push_back(Vec3Df(1.0f, 0.0f, 0.0f));
            vertices.push_back(Vec3Df(0.0f, 0.0f, 0.0f));

            Color color1(1.0f,0.0f,0.0f);
            faces.push_back(Face(0,1,3,color1));
            faces.push_back(Face(1,2,3,color1));

            Color color2(0.0f,1.0f,0.0f);
            faces.push_back(Face(4,5,7,color2));
            faces.push_back(Face(5,6,7,color2));

            Color color3(0.0f,0.0f,1.0f);
            faces.push_back(Face(8,9,11,color3));
            faces.push_back(Face(9,10,11,color3));

            Color color4(1.0f,1.0f,0.0f);
            faces.push_back(Face(13,15,12,color4));
            faces.push_back(Face(13,14,15,color4));

            Color color5(1.0f,0.0f,1.0f);
            faces.push_back(Face(17,19,16,color5));
            faces.push_back(Face(17,18,19,color5));

            Color color6(0.0f,1.0f,1.0f);
            faces.push_back(Face(20,21,23,color6));
            faces.push_back(Face(21,22,23,color6));

            return Model3D(vertices, faces);
        }

        void computeNormals(const Model3D& model, std::vector<Vec3Df>& normals)
        {
            normals.resize(model.getVertices().size());

            for (unsigned int i = 0; i < model.getFaces().size(); i++)
            {
                const Face& face = model.getFaces()[i];

                Vec3Df e01 = model.getVertices()[face[1]] - model.getVertices()[face[0]];
                Vec3Df e02 = model.getVertices()[face[2]] - model.getVertices()[face[0]];
                Vec3Df n = e01.cross(e02);
                n.normalize();

                // test
                n = n * -1.0f;

                normals[face[0]] += n;
                normals[face[1]] += n;
                normals[face[2]] += n;
            }

            for (unsigned int i = 0; i < normals.size(); i++)
                normals[i].normalize();
        }
    }
}
