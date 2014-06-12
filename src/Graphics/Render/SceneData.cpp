#include "SceneData.h"

namespace Graphics
{
    namespace Render
    {
        SceneData::SceneData()
        {
            //ctor
        }

        SceneData::~SceneData()
        {
            // delete root scene node => delete all scene nodes
            delete sceneNodes_[0];
        }

        SceneNode* SceneData::getRootSceneNode()
        {
            return sceneNodes_[0];
        }

        SceneNode* SceneData::getLastSceneNode()
        {
            return sceneNodes_.back();
        }

        SceneNode* SceneData::getEntitySceneNode(const Ecs::Entity& entity)
        {
            unsigned int id = 0;
            if (getEntitySceneNodeId(entity, id))
                return sceneNodes_[id];
            else
                return NULL;
        }

        void SceneData::addSceneNode(SceneNode* node)
        {
            sceneNodes_.push_back(node);
            getLastSceneNode()->setId(sceneNodes_.size()-1);
        }

        void SceneData::setLastSceneNodeEntity(const Ecs::Entity& entity)
        {
            sceneNodeIdsByEntity_[entity] = getLastSceneNode()->getId();
        }

        bool SceneData::getEntitySceneNodeId(Ecs::Entity entity, unsigned int& id)
        {
            if (sceneNodeIdsByEntity_.find(entity) != sceneNodeIdsByEntity_.end())
            {
                id = sceneNodeIdsByEntity_[entity];
                return true;
            }
            else
                return false;
        }
    }
}
