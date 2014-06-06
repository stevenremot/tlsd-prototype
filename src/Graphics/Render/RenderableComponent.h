#ifndef GRAPHICS_RENDER_RENDERABLECOMPONENT_H
#define GRAPHICS_RENDER_RENDERABLECOMPONENT_H

#include <string>

#include "../../Ecs/Component.h"
#include "../../Geometry/PositionComponent.h"
#include "../../Geometry/RotationComponent.h"
#include "Model3D.h"

namespace Graphics
{
    namespace Render
    {
        using std::string;

        class RenderableComponent : public Ecs::Component
        {
        public:
            static const Ecs::Component::Type Type;

            RenderableComponent(const Model3D& model3d, const string& meshFileName, const string& textureFileName):
                Component(Type),
                model3d_(model3d),
                meshFileName_(meshFileName),
                textureFileName_(textureFileName)
            {}

            RenderableComponent(const Model3D& model3d):
                Component(Type),
                model3d_(model3d),
                meshFileName_(""),
                textureFileName_("")
            {}

            RenderableComponent(const string& meshFileName, const string& textureFileName):
                Component(Type),
                model3d_(Model3D()),
                meshFileName_(meshFileName),
                textureFileName_(textureFileName)
            {}

            virtual const std::vector<Ecs::Component::Type>& getDependentComponents()
            {
                if (Dependencies.empty())
                {
                    Dependencies.push_back(Geometry::PositionComponent::Type);
                    Dependencies.push_back(Geometry::RotationComponent::Type);
                }
                return Dependencies;
            }

            const Model3D& getModel3d() const
            {
                return model3d_;
            }

            const string& getMeshFileName() const
            {
                return meshFileName_;
            }

            const string& getTextureFileName() const
            {
                return textureFileName_;
            }

        private:
            Model3D model3d_;
            string meshFileName_;
            string textureFileName_;

            static std::vector<Ecs::Component::Type> Dependencies;
        };
    }
}
#endif // GRAPHICS_RENDER_RENDERABLECOMPONENT_H
