#ifndef GRAPHICS_RENDER_RENDEREVENTS_H
#define GRAPHICS_RENDER_RENDEREVENTS_H

#include <string>

#include "../../Event/Event.h"
#include "../../Geometry/Vec3D.h"
#include "Model3D.h"
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
    }
}
#endif // GRAPHICS_RENDER_RENDEREVENTS_H
