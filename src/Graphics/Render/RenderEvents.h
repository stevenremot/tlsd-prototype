#ifndef GRAPHICS_RENDER_RENDEREVENTS_H
#define GRAPHICS_RENDER_RENDEREVENTS_H

#include <string>

#include "../../Event/Event.h"
#include "../../Geometry/Vec3D.h"
#include "Model3D.h"
#include "../../Ecs/Entity.h"

using std::string;
using Geometry::Vec3Df;

namespace Graphics
{
    namespace Render
    {
        class RenderMeshFileEvent : public Event::Event
        {
        public:
            static const Event::Type TYPE;

            RenderMeshFileEvent(const string& meshFile, const string& textureFile, const Vec3Df& position, const Vec3Df& rotation, const Ecs::Entity& entity):
                Event::Event(TYPE),
                meshFile_(meshFile),
                textureFile_(textureFile),
                position_(position),
                rotation_(rotation),
                entity_(entity)
            {}

            const string& getMeshFile() const
            {
                return meshFile_;
            }

            const string& getTextureFile() const
            {
                return textureFile_;
            }

            const Vec3Df& getPosition() const
            {
                return position_;
            }

            const Vec3Df& getRotation() const
            {
                return rotation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const string& meshFile_;
            const string& textureFile_;
            const Vec3Df& position_;
            const Vec3Df& rotation_;
            Ecs::Entity entity_;
        };

        class RenderAnimatedMeshFileEvent : public Event::Event
        {
        public:
            static const Event::Type TYPE;

            RenderAnimatedMeshFileEvent(const string& meshFile, const string& textureFile, const Vec3Df& position, const Vec3Df& rotation, const Ecs::Entity& entity):
                Event::Event(TYPE),
                meshFile_(meshFile),
                textureFile_(textureFile),
                position_(position),
                rotation_(rotation),
                entity_(entity)
            {}

            const string& getMeshFile() const
            {
                return meshFile_;
            }

            const string& getTextureFile() const
            {
                return textureFile_;
            }

            const Vec3Df& getPosition() const
            {
                return position_;
            }

            const Vec3Df& getRotation() const
            {
                return rotation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const string& meshFile_;
            const string& textureFile_;
            const Vec3Df& position_;
            const Vec3Df& rotation_;
            Ecs::Entity entity_;
        };

        class RenderModel3DEvent : public Event::Event
        {
        public:
            static const Event::Type TYPE;

            RenderModel3DEvent(const Model3D& model, const Vec3Df& position, const Vec3Df& rotation, const Ecs::Entity& entity):
                Event::Event(TYPE),
                model_(model),
                position_(position),
                rotation_(rotation),
                entity_(entity)
            {}

            const Model3D& getModel() const
            {
                return model_;
            }

            const Vec3Df& getPosition() const
            {
                return position_;
            }

            const Vec3Df& getRotation() const
            {
                return rotation_;
            }

            const Ecs::Entity& getEntity() const
            {
                return entity_;
            }

        private:
            const Model3D& model_;
            const Vec3Df& position_;
            const Vec3Df& rotation_;
            const Ecs::Entity& entity_;
        };
    }
}
#endif // GRAPHICS_RENDER_RENDEREVENTS_H
