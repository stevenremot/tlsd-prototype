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
#include "CityGeneration.h"
#include "../Ground.h"
#include "../SimpleTree.h"

using Graphics::Render::RenderableComponent;
using Geometry::Vec3Df;
using Geometry::Vec2Df;

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

            Chunk::EntityCollection& finalEntities = currentChunk.getFinalEntities();
            const Chunk::EntityCollection& baseEntities =
                currentChunk.getBaseEntities();

            for (unsigned int i = 0; i < baseEntities.size(); i++)
            {
                finalEntities.push_back(baseEntities[i]);
            }

            finalEntities.push_back(createGround(world_, x, y));

            Random::NumberGenerator rng(getChunkSeed(x, y));
            std::vector<Geometry::Vec3Df> positions;
            std::vector<SimpleTree*> trees;
            generateTrees(x, y, rng, positions, trees);

            unsigned int length = positions.size();

            for (unsigned int i = 0; i < length; i++)
            {
                finalEntities.push_back(createTree(positions[i], *(trees[i])));
                delete trees[i];
            }

            Threading::ConcurrentWriter<Ecs::World> ecsWorld =
                ecsWorld_.getWriter();

            for (unsigned int i = 0; i < finalEntities.size(); i++)
            {
                ecsWorld->loadDescriptor(*(finalEntities[i]));
            }

            world_.setChunk(x, y, currentChunk);
        }

        void ChunkGenerator::unGenerateChunk(int x, int y)
        {
            Chunk currentChunk;

            if (world_.getChunk(x, y, currentChunk) &&
                currentChunk.getState() == Chunk::GeneratedState)
            {
                Chunk::EntityCollection& finalEntities =
                    currentChunk.getFinalEntities();

                Threading::ConcurrentWriter<Ecs::World> ecsWorld =
                    ecsWorld_.getWriter();

                for (unsigned int i = 0; i < finalEntities.size(); i++)
                {
                    ecsWorld->unloadDescriptor(*(finalEntities[i]));
                }

                finalEntities.clear();
                currentChunk.setState(Chunk::PreparedState);
                world_.setChunk(x, y, currentChunk);
            }
        }

        void ChunkGenerator::removeChunk(int x, int y)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    unGenerateChunk(x + i, y + j);
                }
            }

            Chunk currentChunk;
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

            if ((x == 0 && y == 0) || rng.getUniform(0, 50) < 1)
            {
                generateCity(x, y, rng);
            }
        }

        void ChunkGenerator::generateCity(int x, int y, Random::NumberGenerator& rng)
        {
            const float chunkSize = World::ChunkSize;
            const float floatX = x, floatY = y;
            float centerX, centerY;

            if (x == 0 && y == 0)
            {
                centerX = centerY = 0;
            }
            else
            {
                // TODO We should not restrain to center of the chunk,
                //      This is done to avoid inconsistent chunk generation.
                //      chunk generation should be improved to be more robust
                centerX = rng.getUniform(
                    (floatX + 0.33) * chunkSize,
                    (floatX + 0.66) * chunkSize
                );
                centerY = rng.getUniform(
                    (floatY + 0.33) * chunkSize,
                    (floatY + 0.66) * chunkSize
                );
            }

            const Geometry::Vec2Df position(centerX, centerY);
            const City::GenerationParameters parameters;

            class City* city = Generation::generateCity(position, parameters, rng);


            Core::SharedPtr<Ecs::EntityDescriptor> roadPtr =
                createRoad(city->getRoadNetwork());
            insertDescriptor(roadPtr, x, y);

            const std::vector<BuildingInterface*>& buildings = city->getBuildings();
            for (unsigned int i = 0; i < buildings.size(); i++)
            {
                Core::SharedPtr<Ecs::EntityDescriptor> buildingPtr =
                    createBuilding(*(buildings[i]));
                insertDescriptor(buildingPtr, x, y);
            }

            BiomeMap& biomeMap = world_.getBiomeMap();
            biomeMap.addCityPolygon(
                city->getRoadNetwork().getConvexHull()
            );

            delete city;
        }

        void ChunkGenerator::generateTrees(int x, int y, Random::NumberGenerator& rng, std::vector<Geometry::Vec3Df>& positions, std::vector<SimpleTree*>& trees)
        {
            const float chunkSize = World::ChunkSize;
            const unsigned int treeDensity = World::TreeDensity;
            const float floatX = x, floatY = y;
            Chunk chunk;
            world_.getChunk(x, y, chunk);

            for (unsigned int i = 0; i < treeDensity; i++)
            {
                // Generate the parameters
                float localX = rng.getUniform(0,chunkSize);
                float localY = rng.getUniform(0,chunkSize);
                float truncHeight = rng.getUniform(4,10);
                float truncWidth = rng.getUniform(0.5,3);
                float leavesHeight = rng.getUniform(1,3);
                float leavesWidth = rng.getUniform(truncWidth+2,truncWidth+5);
                float offset = rng.getUniform(0,0.3);
                float truncR = rng.getUniform(0.2,0.4);
                float truncG = rng.getUniform(0.05,0.15);
                float truncB = rng.getUniform(0.01,0.04);
                float leavesR = rng.getUniform(0.05,0.15);
                float leavesG = rng.getUniform(0.2,0.6);
                float leavesB = rng.getUniform(0.1,0.2);
                const std::vector<Geometry::Polygon2D> cityPolygons = world_.getBiomeMap().getCityPolygons();
                unsigned int length = cityPolygons.size();
                // Test to see if the future tree will be in a city
                bool isInACity = false;
                for (unsigned int j = 0; j < length; j++)
                {
                    if (cityPolygons[j].contains(Vec2Df(localX + floatX*chunkSize, localY + floatY*chunkSize)))
                    {
                        isInACity = true;
                    }
                }
                // Insert the tree in the trees list
                if (!isInACity)
                {
                    positions.push_back(Vec3Df(localX + floatX*chunkSize, localY + floatY*chunkSize, computeHeight(world_, floatX*chunkSize + localX, floatY*chunkSize + localY)));
                    SimpleTree *tree = new SimpleTree(truncHeight,truncWidth,leavesHeight,leavesWidth,offset,Graphics::Color(truncR,truncG,truncB),Graphics::Color(leavesR,leavesG,leavesB));
                    trees.push_back(tree);
                }
            }
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
                        const Graphics::Render::Model3D& model =
                            renderable.getModel3d();

                        const std::vector<Geometry::Vec3Df>& vertices =
                            model.getVertices();

                        // We can assume the model has vertices,
                        // otherwise it must be an error
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

                        isRenderable = true;
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
                const Vec3Df offsetMax = (offset + max) / static_cast<float>(World::ChunkSize);
                const Geometry::Vec2Di planMin(
                    floor(offsetMin.getX()),
                    floor(offsetMin.getY())
                );
                const Geometry::Vec2Di planMax(
                    ceil(offsetMax.getX()),
                    ceil(offsetMax.getY())
                );

                for (int i = planMin.getX(); i < planMax.getX(); i++)
                {
                    for (int j = planMin.getY(); j < planMax.getY(); j++)
                    {
                        Chunk chunk;
                        world_.getChunk(i, j, chunk); // Don't care if it fails

                        Chunk::EntityCollection& entities = chunk.getBaseEntities();
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
                chunk.setBaseEntities(entities);

                world_.setChunk(defaultI, defaultJ, chunk);
            }
        }
    }
}
