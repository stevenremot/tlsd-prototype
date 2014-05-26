#ifndef MODELUTILS_H
#define MODELUTILS_H

#include "Model3D.h"

namespace Graphics
{
    namespace Render
    {
        Model3D createCubeModel(const Color& color);
        void computeNormals(const Model3D& model, std::vector<Geometry::Vec3Df>& normals);
    }
}

#endif // MODELUTILS_H
