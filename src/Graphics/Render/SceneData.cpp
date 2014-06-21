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

        bool SceneData::hasId(const Ecs::Entity& entity, unsigned int id)
        {
            unsigned int eId = 0;
            if (getEntitySceneNodeId(entity, eId))
                return eId == id;
            else
                return false;
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
