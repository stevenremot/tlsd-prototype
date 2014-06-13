#include "CollisionEngine.h"

#include <vector>
#include <irrlicht/ISceneCollisionManager.h>
#include "InitCollisionEngineEvent.h"
#include "../Graphics/Render/MeshSceneNode.h"
#include "../Geometry/IrrlichtConversions.h"

using irr::core::vector3df;

#include <iostream>

namespace Physics
{
    void CollisionEngine::call(const Event::Event& event)
    {
        if (event.getType() == InitCollisionEngineEvent::TYPE)
        {
            const InitCollisionEngineEvent& initEvent = static_cast<const InitCollisionEngineEvent&>(event);
            irrlichtSceneManager_= initEvent.getManager();
            data_ = initEvent.getData();
        }
    }

    void CollisionEngine::run()
    {
        if (!isInitialized())
            return;

        std::vector<Ecs::Entity> delayedCommands_;

        while (!selectorCreationCommands_.isEmpty())
        {
            Ecs::Entity entity = 0;
            selectorCreationCommands_ >> entity;

            if (!addSelector(entity))
                delayedCommands_.push_back(entity);
        }

        for (unsigned int i = 0; i < delayedCommands_.size(); i++)
            selectorCreationCommands_ << delayedCommands_[i];
    }

    bool CollisionEngine::getGroundCollisionResponse(
        const Ecs::Entity& movingEntity,
        const Ecs::Entity& groundEntity,
        Geometry::Vec3Df& position,
        const Geometry::Vec3Df& movementVector)
    {
        Graphics::Render::SceneNode* movingNode = data_->getEntitySceneNode(movingEntity);

        // in this case the scene node has not yet been initialized
        if (movingNode == NULL)
            return false;

        irr::scene::ISceneNode* movingSceneNode = movingNode->getIrrlichtSceneNode();
        vector3df dims = 0.5f * movingSceneNode->getBoundingBox().getExtent() * movingSceneNode->getScale();
        Geometry::Vec3Df previousPos = position - movementVector;
        vector3df pos = Geometry::fromVec3Df(previousPos);
        pos += vector3df(0,dims.Y,0);

        vector3df gravity = vector3df(0,0,0);
        vector3df velocity = Geometry::fromVec3Df(movementVector);
        if (velocity.Y < 0)
        {
            // apply the vertical movement afterwards
            gravity.Y = velocity.Y;
            velocity.Y = 0;
        }

        irr::core::triangle3df triout;
        vector3df hitPosition;
        bool outFalling;
        irr::scene::ISceneNode* outNode = NULL;

        std::map<Ecs::Entity, irr::scene::ITriangleSelector*>::iterator selectorIt =
        selectors_.find(groundEntity);
        // in this case the ground selector has not yet been initialized
        if (selectorIt == selectors_.end())
            return false;

        vector3df newPosition = irrlichtSceneManager_->getSceneCollisionManager()->getCollisionResultPosition(
                          selectorIt->second,
                          pos,
                          dims,
                          velocity,
                          triout,
                          hitPosition,
                          outFalling,
                          outNode,
                          0.0005f,
                          gravity // gravity is already taken into account in the MovementSystem
                      );
        newPosition -= vector3df(0,dims.Y,0);
        position = Geometry::fromIrrVector3df(newPosition);

        return outNode != NULL;
    }

    void CollisionEngine::addSelectorCreationCommand(const Ecs::Entity& entity)
    {
        selectorCreationCommands_ << entity;
    }

    bool CollisionEngine::addSelector(const Ecs::Entity& entity)
    {
        Graphics::Render::SceneNode* node = data_->getEntitySceneNode(entity);

        if (node != NULL)
        {
            Graphics::Render::MeshSceneNode* meshNode = dynamic_cast<Graphics::Render::MeshSceneNode*>(node);
            selectors_[entity] =
                irrlichtSceneManager_->createTriangleSelector(meshNode->getIrrlichtMesh(), meshNode->getIrrlichtSceneNode());
            return true;
        }
        else
            return false;
    }
}
