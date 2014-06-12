#ifndef PHYSICS_COLLISIONENGINE_H
#define PHYSICS_COLLISIONENGINE_H

#include <map>
#include <irrlicht/ISceneCollisionManager.h>
#include <irrlicht/ITriangleSelector.h>
#include "../Ecs/Entity.h"
#include "../Geometry/Vec3D.h"
#include "../Graphics/Render/SceneData.h"

namespace Physics
{
    /**
    *   Simple collision engine using Irrlicht's CollisionManager
    */
    class CollisionEngine
    {
    public:
        CollisionEngine(Graphics::Render::SceneData& data):
            data_(data)
            {}
        virtual ~CollisionEngine();

        /**
        * Apply collision response to the movingEntity against the groundEntity
        * @return true if there was a collision
        * The input position Vec3Df is updated at its new position
        */
        bool getGroundCollisionResponse(
            Ecs::Entity movingEntity,
            Ecs::Entity groundEntity,
            const Geometry::Vec3Df& velocity,
            Geometry::Vec3Df& position
        );

    private:
        irr::scene::ISceneCollisionManager* collisionManager_;
        std::map<Ecs::Entity, irr::scene::ITriangleSelector*> groundSelectors_;

        Graphics::Render::SceneData& data_;
    };
}

#endif // PHYSICS_COLLISIONENGINE_H
