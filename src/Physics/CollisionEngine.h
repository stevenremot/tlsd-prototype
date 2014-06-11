#ifndef PHYSICS_COLLISIONENGINE_H
#define PHYSICS_COLLISIONENGINE_H

#include <map>
#include <irrlicht/ISceneManager.h>
#include <irrlicht/ITriangleSelector.h>
#include "../Ecs/Entity.h"
#include "../Geometry/Vec3D.h"
#include "../Graphics/Render/SceneData.h"
#include "../Event/EventListenerInterface.h"
#include "../Threading/Channel.h"

namespace Physics
{
    /**
    *   Simple collision engine using Irrlicht's CollisionManager
    */
    class CollisionEngine : public Event::EventListenerInterface, Threading::ThreadableInterface
    {
    public:
        CollisionEngine(Graphics::Render::SceneData& data):
            irrlichtSceneManager_(NULL),
            data_(data)
            {}
        virtual ~CollisionEngine();

        virtual void call(const Event::Event& event);

        virtual void run();

        /**
        * Apply collision response to the movingEntity against the groundEntity
        * @return true if there was a collision
        * The input position Vec3Df is updated at its new position
        */
        bool getGroundCollisionResponse(
            const Ecs::Entity& movingEntity,
            const Ecs::Entity& groundEntity,
            Geometry::Vec3Df& position,
            const Geometry::Vec3Df& movementVector
        );

        void addSelectorCreationCommand(const Ecs::Entity& entity);
    private:
        bool addSelector(const Ecs::Entity& groundEntity);

        irr::scene::ISceneManager* irrlichtSceneManager_;
        std::map<Ecs::Entity, irr::scene::ITriangleSelector*> selectors_;

        Graphics::Render::SceneData& data_;

        Threading::Channel<Ecs::Entity> selectorCreationCommands_;
    };
}

#endif // PHYSICS_COLLISIONENGINE_H
