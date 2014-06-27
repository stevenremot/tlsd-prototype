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

#include "CityGeneration.h"

#include "City/RoadExpander.h"
#include "City/NeighbourNodeConstraint.h"
#include "City/NeighbourEdgeConstraint.h"
#include "City/IntersectionConstraint.h"
#include "City/MergeConstraint.h"
#include "City/LotCreation.h"
#include "City/RoadUtil.h"
#include "../SimpleBuilding.h"
#include "../../Graph/PlanarPrimitiveExtraction.h"

using Graph::PlanarGraph;
using Graph::PlanarNode;
using Geometry::Vec2Df;

namespace World
{
    namespace Generation
    {
        RoadNetwork generateBaseRoad(
            const Vec2Df& position,
            const City::GenerationParameters& parameters,
            Random::NumberGenerator& rng
        ) {
            PlanarGraph graph;

            PlanarNode n1 = graph.addNode(position);
            PlanarNode n2 =
                graph.addNode(position - Vec2Df(0, -parameters.getRoadLength()));

            Graph::PlanarEdge e = graph.addEdge(n1, n2);

            const float roadLength = parameters.getRoadLength();

            City::RoadExpander expander(
                City::QueryCreator(
                    roadLength,
                    parameters.getRoadDeviation(),
                    rng
                ),
                RoadNetwork(graph, parameters.getRoadWidth(), parameters.getRoadColor())
            );

            expander.addRoadConstraint(
                new City::NeighbourNodeConstraint(roadLength * 2.0 / 3.0)
            );
            expander.addRoadConstraint(
                new City::NeighbourEdgeConstraint(roadLength * 2.0 / 3.0)
            );
            expander.addRoadConstraint(
                new City::IntersectionConstraint(parameters.getMinRoadLength())
            );
            expander.addRoadConstraint(
                new City::MergeConstraint(parameters.getMinRoadLength(), 0.3)
            );

            expander.addBranchRequest(City::BranchRequest(n1, e));

            for (unsigned int i = 0; i < parameters.getExpansionNumber(); i++)
            {
                expander.expand();
            }

            return expander.getRoadNetwork();
        }

        BuildingInterface* createBuilding(
            const Geometry::Polygon2D& base,
            const City::GenerationParameters& parameters,
            Random::NumberGenerator& rng
        ) {
            const float height = rng.getUniform(
                parameters.getMinBuildingHeight(),
                parameters.getMaxBuildingHeight()
            );

            const Geometry::Vec3Df& wallColorMin = parameters.getWallColorMin();
            const Geometry::Vec3Df& wallColorMax = parameters.getWallColorMax();
            const Geometry::Vec3Df& roofColorMin = parameters.getRoofColorMin();
            const Geometry::Vec3Df& roofColorMax = parameters.getRoofColorMax();

            const float wallCoef = rng.getUniform(0.0, 1.0);
            const Geometry::Vec3Df wallColor =
                wallColorMin * wallCoef + wallColorMax * (1.0 - wallCoef);

            const Geometry::Vec3Df roofColor = Geometry::Vec3Df(
                rng.getUniform(roofColorMin.getX(), roofColorMax.getX()),
                rng.getUniform(roofColorMin.getY(), roofColorMax.getY()),
                rng.getUniform(roofColorMin.getZ(), roofColorMax.getZ())
            );

            return new SimpleBuilding(
                base,
                height * 0.70,
                height * 0.30,
                wallColor,
                roofColor
            );
        }

        class City* generateCity(
            const Vec2Df& position,
            const City::GenerationParameters& parameters,
            Random::NumberGenerator& rng
        ) {
            RoadNetwork road = generateBaseRoad(position, parameters, rng);

            const PlanarGraph& baseGraph = road.getGraph();
            Graph::PlanarPrimitiveCollection primitives =
                Graph::extractPrimitives(baseGraph);

            road.setGraph(Graph::extractFilamentsInCycles(baseGraph, primitives));

            City::LotCollection lots;

            for (unsigned int i = 0; i < primitives.size(); i++)
            {
                const Graph::PlanarPrimitive& prim = primitives[i];
                if (prim.getType() == Graph::PlanarPrimitive::CycleType)
                {
                    const City::LotCollection& newLots = City::createLots(
                        City::convertToPolygon(prim).offset(-parameters.getRoadWidth()),
                        parameters.getMinRoadLength(),
                        parameters.getMaxRoadLength(),
                        rng
                    );

                    lots.insert(lots.end(), newLots.begin(), newLots.end());
                }
            }

            std::vector<BuildingInterface*> buildings;

            for (unsigned int i = 0; i < lots.size(); i++)
            {
                buildings.push_back(
                    createBuilding(
                        lots[i],
                        parameters,
                        rng
                    )
                );
            }

            return new World::City(road, buildings);
        }
    }
}
