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
    }
}
