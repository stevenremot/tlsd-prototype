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

#ifndef PHYSICS_MODEL3DCOLLISIONBODY_H
#define PHYSICS_MODEL3DCOLLISIONBODY_H

#include "CollisionBody.h"
#include "../Graphics/Render/Model3D.h"

namespace Physics
{
    /**
    *   CollisionBody for Renderable entities with few polys : it uses the Model3D itself
    */
    class Model3DCollisionBody : public CollisionBody
    {
    public:
        static const Type Type;

        Model3DCollisionBody(const Graphics::Render::Model3D& model):
            CollisionBody(Type),
            model_(model)
            {}

        virtual CollisionBody* clone()
        {
            return new Model3DCollisionBody(model_);
        }

        const Graphics::Render::Model3D& getModel() const
        {
            return model_;
        }

    private:
        Graphics::Render::Model3D model_;
    };
}

#endif // PHYSICS_MODEL3DCOLLISIONBODY_H
