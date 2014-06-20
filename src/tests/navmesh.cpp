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

#include "navmesh.h"

#include <vector>

#include "../AI/AiComponent.h"
#include "../AI/Sensor/SightSensor.h"
#include "../AI/SubSystems/TargetingSubsystem.h"
#include "../AI/SubSystems/NavigationSubsystem.h"
#include "../AI/NavMesh/NavMeshGenerationEngine.h"
#include "../AI/NavMesh/NavMeshGenerator.h"

#include "../Graph/PathFinding.h"

#include "../Event/EventManager.h"
#include "SvgDrawer.h"
using std::vector;

namespace NavMeshTest
{

    Ecs::Entity createNewCharacter(Ecs::World& w, const AI::NavMesh::NavMeshContainer& navMeshes ,const Geometry::Vec3Df& position, const Geometry::Vec3Df& velocity, bool hasAI)
    {
        Ecs::Entity e = w.createEntity();

        Geometry::PositionComponent* positionComponent = new Geometry::PositionComponent(position);
        Physics::MovementComponent* movementComponent= new Physics::MovementComponent(velocity);
        w.addComponent(e, positionComponent);
        w.addComponent(e, movementComponent);

        if(hasAI)
        {
            AI::AiComponent* aiComponent = new AI::AiComponent(e,w, navMeshes);
            w.addComponent(e, aiComponent);

            // Add a sight sensor
            AI::Sensor::SensorsManager& sensorsManager = aiComponent->getSensorsManager();
            sensorsManager.addSensor(AI::Sensor::SightSensor::Type);

            // Add navigation and targeting subsytems
            AI::Subsystem::SubSystemsManager& subsystemsManager = aiComponent->getSubsystemsManager();
            subsystemsManager.addSubsystem(AI::Subsystem::TargetingSubsystem::Type);
            subsystemsManager.addSubsystem(AI::Subsystem::NavigationSubSystem::Type);
        }
        return e;
    }

    void testNavMesh()
    {
        Event::EventManager m;
        Event::ListenerRegister & reg = m.getListenerRegister();

        AI::NavMesh::NavMeshGenerationEngine navMeshGenerationEngine;
        navMeshGenerationEngine.registerListeners(reg);

        vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(&m);

        Threading::Thread eventThread(threadables, 2);
        eventThread.start();

        vector<Threading::ThreadableInterface*> threadables2;
        threadables2.push_back(&navMeshGenerationEngine);

        Threading::Thread generationThread(threadables2, 2);
        generationThread.start();


        Event::EventQueue & queue = m.getEventQueue();

        Geometry::Vec2Df lowerLeftPoint(0.f, 0.f);
        Geometry::Vec2Df upperRightPoint(128.f,128.f);
        queue << new AI::NavMesh::AreaCreatedEvent(lowerLeftPoint, upperRightPoint);

        // Create some obtacles
        queue << new AI::NavMesh::ObstacleAddedEvent(AI::NavMesh::Obstacle(Geometry::Vec2Df(110.f,110.f), Geometry::Vec2Df(119.f,119.f)));
        queue << new AI::NavMesh::ObstacleAddedEvent(AI::NavMesh::Obstacle(Geometry::Vec2Df(60.f,60.f), Geometry::Vec2Df(70.f,70.f)));
        queue << new AI::NavMesh::ObstacleAddedEvent(AI::NavMesh::Obstacle(Geometry::Vec2Df(10.f,10.f), Geometry::Vec2Df(15.f,15.f)));

        queue << new AI::NavMesh::NavMeshOverEvent(lowerLeftPoint,upperRightPoint);
        int k = 0;
        while (k < 20)
        {
            k++;
            Threading::sleep(0, 200);
        }

        eventThread.stop();
        generationThread.stop();

        // Draw navMesh
        Test::SvgDrawer drawer(256,256);
        const AI::NavMesh::NavMeshContainer::NavMeshesList& navMeshes = navMeshGenerationEngine.getNavMeshes().getNavMeshesList();

        if(navMeshes.size() > 0)
        {
            AI::NavMesh::NavMesh* navMesh = navMeshes.at(0);
            // Path finding
            const Graph::PlanarGraph& graph = navMesh->getGraph();
            const Graph::PlanarNode& startNode = graph.getNodes().front();
            const Graph::PlanarNode& goalNode = graph.getNodes().back();
            Graph::PlanarGraph::NodeCollection path;
            Graph::BasicAStar(graph, startNode, goalNode, path);

            drawNavMesh(*navMesh, drawer);
            drawPath(path, drawer);

            drawer.end();
            std::cout << drawer.getContent().str();
        }

        // Test AI
    }

    void drawNavMesh(const AI::NavMesh::NavMesh& navMesh, Test::SvgDrawer& drawer)
    {
        const Graph::PlanarGraph& graph = navMesh.getGraph();
        drawer.drawGraph(graph);
        const AI::NavMesh::NavMesh::PolygonsMap& polygonsMap = navMesh.getPolygonsMap();
        const AI::NavMesh::NavMesh::VerticesMap& verticesMap = navMesh.getVerticesMap();
        const Graph::PlanarGraph::NodeCollection& nodes = graph.getNodes();
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            const Graph::PlanarNode& node = nodes[i];
            const AI::NavMesh::NavMesh::VerticesIdsList verticesIds = polygonsMap.at(node);
            for (unsigned int j = 0; j < verticesIds.size(); j++)
            {
                if(j != verticesIds.size()-1)
                {
                    const Geometry::Vec2Df& p1 = verticesMap.at(verticesIds[j]);
                    const Geometry::Vec2Df& p2 = verticesMap.at(verticesIds[j+1]);
                    drawer.drawLine(p1.getX(),p1.getY(), p2.getX(), p2.getY(), "blue");
                }
                else
                {
                    const Geometry::Vec2Df& p1 = verticesMap.at(verticesIds[j]);
                    const Geometry::Vec2Df& p2 = verticesMap.at(verticesIds[0]);
                    drawer.drawLine(p1.getX(),p1.getY(), p2.getX(), p2.getY(), "blue");
                }
            }
        }
    }

    void drawPath( const Graph::PlanarGraph::NodeCollection& path, Test::SvgDrawer& drawer)
    {
        if(path.size() <= 0)
            return;
        for (unsigned int i = 0; i < path.size() - 1; i++)
        {
            const Graph::PlanarNode& node = path.at(i);
            const Graph::PlanarNode& nextNode = path.at(i+1);

            const Geometry::Vec2Df& p1 = node.getPosition();
            const Geometry::Vec2Df& p2 = nextNode.getPosition();
            drawer.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), "red");
        }
    }

}
