#include "SceneData.h"

namespace Graphics
{
    namespace Render
    {
        SceneData::SceneData():
            lastSceneNode_(NULL)
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
            return lastSceneNode_;
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
            // Recycle space left by removed scene nodes.
            lastSceneNode_ = node;
            for (unsigned int i = 0; i < sceneNodes_.size(); i++)
            {
                if (sceneNodes_[i] == NULL)
                {
                    sceneNodes_[i] = node;
                    getLastSceneNode()->setId(i);
                }
            }

            sceneNodes_.push_back(node);
            getLastSceneNode()->setId(sceneNodes_.size()-1);
        }

        void SceneData::setLastSceneNodeEntity(const Ecs::Entity& entity)
        {
            sceneNodeIdsByEntity_[entity] = getLastSceneNode()->getId();
        }

        void SceneData::removeSceneNodeEntity(const Ecs::Entity& entity)
        {
            unsigned int id;
            if (getEntitySceneNodeId(entity, id))
            {
                SceneNode* node = sceneNodes_[id];
                sceneNodeIdsByEntity_.erase(entity);

                // TODO find a way to erase and synchronize
                // the nodes witht the entities
                sceneNodes_[id] = NULL;

                if (node != NULL)
                    delete node;
            }

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
