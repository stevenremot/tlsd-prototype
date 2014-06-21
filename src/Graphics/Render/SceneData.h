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

#ifndef GRAPHICS_RENDER_SCENEDATA_H
#define GRAPHICS_RENDER_SCENEDATA_H

#include <map>
#include <vector>
#include "../../Ecs/Entity.h"
#include "SceneNode.h"

namespace Graphics
{
    namespace Render
    {
        /**
        *   Contains the data of the Scene and provides access methods
        */
        class SceneData
        {
        public:
            SceneData();
            virtual ~SceneData();

            SceneNode* getRootSceneNode();
            SceneNode* getLastSceneNode();
            /**
            *   @return null if no scene node found for this entity
            */
            SceneNode* getEntitySceneNode(const Ecs::Entity& entity);
            void addSceneNode(SceneNode* node);
            /**
            *   If the last scene node added was an entity's, register it in the map
            */
            void setLastSceneNodeEntity(const Ecs::Entity& entity);

            /**
            *   Check if an entity has the given id in the scene
            */
            bool hasId(const Ecs::Entity& entity, unsigned int id);

            /**
             * Remove the scene node corresponding to this entity.
             */
            void removeSceneNodeEntity(const Ecs::Entity& entity);

        private:
            /**
            *   @param[in] entity
            *   @param[out] id
            *   @return true if the entity is already drawn on the scene
            */
            bool getEntitySceneNodeId(Ecs::Entity entity, unsigned int& id);

            std::map<Ecs::Entity, unsigned int> sceneNodeIdsByEntity_;
            std::vector<SceneNode*> sceneNodes_;

            unsigned long renderedEntitiesNumber_;
            SceneNode* lastSceneNode_;
        };
    }
}

#endif // GRAPHICS_RENDER_SCENEDATA_H
