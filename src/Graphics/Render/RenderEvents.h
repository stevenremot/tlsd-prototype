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

#ifndef GRAPHICS_RENDER_RENDEREVENTS_H
#define GRAPHICS_RENDER_RENDEREVENTS_H

#include <string>

#include "../../Event/Event.h"
#include "../../Geometry/Vec3D.h"
#include "Model3D.h"
#include "CameraSceneNode.h"
#include "../../Ecs/Entity.h"

namespace Graphics
{
    namespace Render
    {
        class RenderMeshFileEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            RenderMeshFileEvent(const std::string& meshFile, const std::string& textureFile, const Geometry::Vec3Df& position, const Geometry::Vec3Df& rotation, const Ecs::Entity& entity):
                Event::Event(Type),
                meshFile_(meshFile),
                textureFile_(textureFile),
                position_(position),
                rotation_(rotation),
                entity_(entity)
            {}

            const std::string& getMeshFile() const
            {
                return meshFile_;
            }

            const std::string& getTextureFile() const
            {
                return textureFile_;
            }

            const Geometry::Vec3Df& getPosition() const
            {
                return position_;
            }

            const Geometry::Vec3Df& getRotation() const
            {
                return rotation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const std::string& meshFile_;
            const std::string& textureFile_;
            const Geometry::Vec3Df& position_;
            const Geometry::Vec3Df& rotation_;
            Ecs::Entity entity_;
        };

        class RenderAnimatedMeshFileEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            RenderAnimatedMeshFileEvent(const std::string& meshFile, const std::string& textureFile, const Geometry::Vec3Df& position, const Geometry::Vec3Df& rotation, const Ecs::Entity& entity):
                Event::Event(Type),
                meshFile_(meshFile),
                textureFile_(textureFile),
                position_(position),
                rotation_(rotation),
                entity_(entity)
            {}

            const std::string& getMeshFile() const
            {
                return meshFile_;
            }

            const std::string& getTextureFile() const
            {
                return textureFile_;
            }

            const Geometry::Vec3Df& getPosition() const
            {
                return position_;
            }

            const Geometry::Vec3Df& getRotation() const
            {
                return rotation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const std::string& meshFile_;
            const std::string& textureFile_;
            const Geometry::Vec3Df& position_;
            const Geometry::Vec3Df& rotation_;
            Ecs::Entity entity_;
        };

        class RenderModel3DEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            RenderModel3DEvent(const Model3D& model, const Geometry::Vec3Df& position, const Geometry::Vec3Df& rotation, const Ecs::Entity& entity):
                Event::Event(Type),
                model_(model),
                position_(position),
                rotation_(rotation),
                entity_(entity)
            {}

            const Model3D& getModel() const
            {
                return model_;
            }

            const Geometry::Vec3Df& getPosition() const
            {
                return position_;
            }

            const Geometry::Vec3Df& getRotation() const
            {
                return rotation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const Model3D& model_;
            const Geometry::Vec3Df& position_;
            const Geometry::Vec3Df& rotation_;
            Ecs::Entity entity_;
        };

        /**
        *   Event used to initialize a camera behind the entity
        */
        class RenderCameraEvent : public Event::Event
        {
        public:
            static const Event::Type Type;

            RenderCameraEvent(const Ecs::Entity& entity) :
                Event(Type),
                entity_(entity)
            {}

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            Ecs::Entity entity_;
        };

        /**
         * Dispatched when the scene has initialized the camera.
         */
        class CameraRenderedEvent: public Event::Event
        {
        public:
            static const Type Type;

            CameraRenderedEvent(CameraSceneNode* camera):
                Event(Type),
                camera_(camera)
            {}

            CameraSceneNode* getCamera() const
            {
                return camera_;
            }

        private:
            CameraSceneNode* camera_;
        };
    }
}
#endif // GRAPHICS_RENDER_RENDEREVENTS_H
