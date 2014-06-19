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

            SceneNode* lastSceneNode_;
        };
    }
}

#endif // GRAPHICS_RENDER_SCENEDATA_H
