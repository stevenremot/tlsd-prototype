#include "CollisionEngine.h"

#include <vector>
#include "InitCollisionEngineEvent.h"
#include "../Graphics/Render/MeshSceneNode.h"



namespace Physics
{
    void CollisionEngine::call(const Event::Event& event)
    {
        const InitCollisionEngineEvent& initEvent = static_cast<const InitCollisionEngineEvent&>(event);
        irrlichtSceneManager_= initEvent.getManager();
    }

    void CollisionEngine::run()
    {
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
        return false;
    }

    void CollisionEngine::addSelectorCreationCommand(const Ecs::Entity& entity)
    {
        selectorCreationCommands_ << entity;
    }

    bool CollisionEngine::addSelector(const Ecs::Entity& entity)
    {
        Graphics::Render::SceneNode* node = data_.getEntitySceneNode(entity);

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
