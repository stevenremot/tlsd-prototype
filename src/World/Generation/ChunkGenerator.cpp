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

#include "ChunkGenerator.h"

#include <cmath>

#include "../EntityCreator.h"
#include "CoefficientsGenerator.h"
#include "../../Graphics/Render/RenderableComponent.h"

using Graphics::Render::RenderableComponent;
using Geometry::Vec3Df;

namespace World
{
    namespace Generation
    {

        Random::Seed ChunkGenerator::getChunkSeed(int x, int y)
        {
            // Use more robust seed generator (z-order?)
            return worldSeed_ + static_cast<Random::Seed>(x + y * y);
        }

        void ChunkGenerator::generateChunk(int x, int y)
        {
            Chunk currentChunk;
            if (world_.getChunk(x, y, currentChunk) &&
                currentChunk.getState() == Chunk::GeneratedState) {
                return;
            }

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    prepareChunk(x + i, y + j);
                }
            }

            world_.getChunk(x, y, currentChunk);
            currentChunk.setState(Chunk::GeneratedState);
            world_.setChunk(x, y, currentChunk);

            Chunk::EntityCollection finalEntities;

            finalEntities.push_back(createGround(world_, x, y));

            currentChunk.setFinalEntities(finalEntities);

            for (unsigned int i = 0; i < finalEntities.size(); i++)
            {
                ecsWorld_.loadDescriptor(*(finalEntities[i]));
            }

            world_.setChunk(x, y, currentChunk);
        }

        void ChunkGenerator::prepareChunk(int x, int y)
        {
            Chunk currentChunk;
            if (world_.getChunk(x, y, currentChunk) &&
                currentChunk.getState() != Chunk::NotLoadedState)
            {
                return;
            }

            Random::NumberGenerator rng(getChunkSeed(x, y));

            BiomeMap& biomeMap = world_.getBiomeMap();
            biomeMap.setPerlinCoef(x, y, generatePerlinCoefficient(rng));

            currentChunk.setCoefficients(generateGroundCoefficients(rng));

            currentChunk.setState(Chunk::PreparedState);
            world_.setChunk(x, y, currentChunk);
        }


        void ChunkGenerator::insertDescriptor(
            Core::SharedPtr<Ecs::EntityDescriptor>& descriptor,
            int defaultI,
            int defaultJ
        ) {
            const std::vector<Ecs::Component*>& components = descriptor->getComponents();

            Geometry::Vec3Df min, max, offset;
            bool isRenderable = false;

            for (unsigned int i = 0; i < components.size(); i++)
            {
                Ecs::Component& component = *(components[i]);
                if (component.getType() == RenderableComponent::Type)
                {
                    RenderableComponent& renderable =
                        dynamic_cast<RenderableComponent&>(component);

                    if (renderable.getMeshFileName().empty())
                    {
                        isRenderable = true;
                        const Graphics::Render::Model3D& model =
                            renderable.getModel3d();

                        const std::vector<Geometry::Vec3Df>& vertices =
                            model.getVertices();

                        min = max = vertices[0];

                        for (unsigned int i = 1; i < vertices.size(); i++)
                        {
                            const Geometry::Vec3Df& vertex = vertices[i];
                            if (vertex.getX() < min.getX())
                            {
                                min.setX(vertex.getX());
                            }
                            if (vertex.getX() > max.getX())
                            {
                                max.setX(vertex.getX());
                            }

                            if (vertex.getY() < min.getY())
                            {
                                min.setY(vertex.getY());
                            }
                            if (vertex.getY() > max.getY())
                            {
                                max.setY(vertex.getY());
                            }
                        }
                    }
                }
                else if(component.getType() == Geometry::PositionComponent::Type)
                {
                    Geometry::PositionComponent& posComp =
                        dynamic_cast<Geometry::PositionComponent&>(component);
                    offset = posComp.getPosition();
                }
            }

            if (isRenderable)
            {
                const Vec3Df offsetMin = (offset + min) / static_cast<float>(World::ChunkSize);
                const Vec3Df offsetMax = offset + max;
                const Geometry::Vec2Di planMin(
                    floor(offsetMin.getX()),
                    floor(offsetMin.getY())
                );
                const Geometry::Vec2Di planMax(
                    ceil(offsetMax.getX()),
                    ceil(offsetMax.getY())
                );

                for (int i = planMin.getX(); i <= planMax.getX(); i++)
                {
                    for (int j = planMin.getY(); j <= planMax.getY(); j++)
                    {
                        Chunk chunk;
                        world_.getChunk(i, j, chunk); // Don't care if it fails

                        Chunk::EntityCollection entities = chunk.getBaseEntities();
                        entities.push_back(descriptor);

                        world_.setChunk(i, j, chunk);
                    }
                }
            }
            else
            {
                Chunk chunk;
                world_.getChunk(defaultI, defaultJ, chunk); // Don't care if it fails

                Chunk::EntityCollection entities = chunk.getBaseEntities();
                entities.push_back(descriptor);

                world_.setChunk(defaultI, defaultJ, chunk);
            }
        }
    }
}
