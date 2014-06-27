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
#include <iostream>

#include "../AI/AiComponent.h"
#include "../AI/BasicAiModule.h"
#include "../AI/AiSystem.h"
#include "../AI/MemoryComponent.h"
#include "../AI/Sensor/SensorSystem.h"
#include "../AI/Sensor/SensorComponent.h"
#include "../AI/Sensor/SightSensor.h"
#include "../AI/SubSystems/TargetingSystem.h"
#include "../AI/SubSystems/NavigationSubsystem.h"
#include "../AI/SubSystems/TargetingSystem.h"
#include "../AI/NavMesh/NavMeshGenerationEngine.h"
#include "../AI/NavMesh/NavMeshGenerator.h"

#include "../Event/EventManager.h"

#include "../Graph/PathFinding.h"

#include "../Physics/MovementSystem.h"

#include "stateMachine.h"
#include "SvgDrawer.h"
using std::vector;
using std::cout;
using std::endl;

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
            // Set up the ai component
            AI::AiComponent* aiComponent = new AI::AiComponent(e, navMeshes);
            AI::MemoryComponent* memoryComponent = new AI::MemoryComponent();
            AI::Sensor::SensorComponent* sensorComponent = new AI::Sensor::SensorComponent(e);
            AI::Subsystem::TargetingComponent* targetingComponent = new AI::Subsystem::TargetingComponent();

            w.addComponent(e, memoryComponent);
            w.addComponent(e, sensorComponent);
            w.addComponent(e, targetingComponent);

            AI::BasicAiModule* aiModule = new AI::BasicAiModule(StateMachineTest::Idle);
            StateMachineTest::setupStateMachine(*aiModule);
            aiComponent->setAiModule(aiModule);
            w.addComponent(e, aiComponent);

            // Add a sight sensor
            AI::Sensor::SensorsManager& sensorsManager = sensorComponent->getSensorsManager();
            sensorsManager.addSensor(AI::Sensor::SightSensor::Type);

            // Add navigation and targeting subsytems
            AI::Subsystem::SubSystemsManager& subsystemsManager = aiComponent->getSubsystemsManager();
            //subsystemsManager.addSubsystem(AI::Subsystem::TargetingSubsystem::Type, w);
            subsystemsManager.addSubsystem(AI::Subsystem::NavigationSubSystem::Type, w);
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
            //drawPath(path, drawer);
            //std::cout << drawer.getContent().str();
        }

        // Test AI
        // Create entity
        Ecs::World w = Ecs::World();
        Ecs::Entity e1 = createNewCharacter(w, navMeshGenerationEngine.getNavMeshes(), Geometry::Vec3Df(0.0,0.0,0.0), Geometry::Vec3Df(0.0,0.0,0.0), true);
        Ecs::Entity e2 = createNewCharacter(w, navMeshGenerationEngine.getNavMeshes(), Geometry::Vec3Df(80.0,80.0,0.0), Geometry::Vec3Df(0.0,0.0,0.0));
        // Create thrads for systems
        AI::AiSystem aiSystem(w);
        AI::Sensor::SensorSystem sensorSystem(w);
        Physics::MovementSystem movementSystem(w);
        AI::Subsystem::TargetingSystem targetingSystem(w);

        vector<Threading::ThreadableInterface*> aiSystemVector;
        vector<Threading::ThreadableInterface*> movementSystemVector;
        vector<Threading::ThreadableInterface*> targetingSystemVector;
        vector<Threading::ThreadableInterface*> sensorSystemVector;

        aiSystemVector.push_back(&sensorSystem);
        aiSystemVector.push_back(&targetingSystem);
        aiSystemVector.push_back(&aiSystem);
        movementSystemVector.push_back(&movementSystem);

        Threading::Thread aiThread(aiSystemVector, 20);
        //Threading::Thread sensorThread(sensorSystemVector, 5);
        //Threading::Thread targetingThread(targetingSystemVector, 5);

        Threading::Thread movementThread(movementSystemVector, 20);

        // Get the position component of e1
        Ecs::ComponentGroup::ComponentTypeCollection types;
        types.insert(Geometry::PositionComponent::Type);

        Ecs::ComponentGroup prototype(types);
        Ecs::ComponentGroup componentsE1 = w.getEntityComponents(e1, prototype);
        const Geometry::PositionComponent& positionComponentE1 = static_cast<const Geometry::PositionComponent&>(componentsE1.getComponent(Geometry::PositionComponent::Type));
        Ecs::ComponentGroup componentsE2 = w.getEntityComponents(e2, prototype);
        Geometry::PositionComponent& positionComponentE2 = static_cast<Geometry::PositionComponent&>(componentsE2.getComponent(Geometry::PositionComponent::Type));

        //sensorThread.start();
        //targetingThread.start();
        aiThread.start();
        movementThread.start();
        std::vector<Geometry::Vec2Df> positions;
        positions.push_back(Geometry::Vec2Df(0,0));
        /*
        bool b = true;
        while(b)
        {
            Geometry::Vec2Df lastPos = positions.back();
            Geometry::Vec3Df pos = positionComponentE1.getPosition();
            if((pos -positionComponentE2.getPosition()).getLength() < 2.f)
                b = false;
            Threading::sleep(0,20);
            if(pos.getX() != lastPos.getX() && pos.getY() != lastPos.getY())
                positions.push_back(Geometry::Vec2Df(pos.getX(), pos.getY()));

        }

        for (int j =0; j < 20; j++)
        {
            Threading::sleep(0,100);
        }
        */

        std::vector<Geometry::Vec2Df> positionsE2;
        std::vector<Geometry::Vec2Df> targets;

        types.insert(AI::Subsystem::TargetingComponent::Type);
        Ecs::ComponentGroup components = w.getEntityComponents(e1, Ecs::ComponentGroup(types));
        const AI::Subsystem::TargetingComponent& targetingComponent = static_cast<const AI::Subsystem::TargetingComponent&>(components.getComponent(AI::Subsystem::TargetingComponent::Type));


        // Taget is moving slowly to the upper-right corner of the navMesh
        Geometry::Vec3Df offset(0.1, -0.2, 0.0);
        for (int j =0; j < 20*20; j++)
        {
            Threading::sleep(0,50);
            Geometry::Vec3Df pos1 = positionComponentE1.getPosition();
            Geometry::Vec3Df pos2 = positionComponentE2.getPosition();
            Geometry::Vec3Df target = targetingComponent.getTargetPosition();

            Geometry::Vec3Df newPos = pos2 + offset;
            positionComponentE2.setPosition(newPos);
            positionsE2.push_back(Geometry::Vec2Df(newPos.getX(), newPos.getY()));
            positions.push_back(Geometry::Vec2Df(pos1.getX(), pos1.getY()));
            targets.push_back(Geometry::Vec2Df(target.getX(), target.getY()));


        }

        aiThread.stop();
        //sensorThread.stop();
        //targetingThread.stop();
        movementThread.stop();

        if(navMeshes.size() > 0)
        {
            AI::NavMesh::NavMesh* navMesh = navMeshes.at(0);
            // Path finding
            const Graph::PlanarGraph& graph = navMesh->getGraph();
            Geometry::Vec3Df pos2 = positionComponentE2.getPosition();

            Graph::PlanarNode startNode; navMesh->getNode( Geometry::Vec2Df(0, 0), startNode);
            Graph::PlanarNode goalNode; navMesh->getNode( Geometry::Vec2Df(pos2.getX(), pos2.getY()), goalNode);
            Graph::PlanarGraph::NodeCollection path;
            Graph::BasicAStar(graph, startNode, goalNode, path);

            drawPath(path, drawer);
        }

        for(unsigned int i = 0; i < positions.size(); i++)
        {
            Geometry::Vec2Df pos = positions[i];
            drawer.drawCircle(pos.getX(), pos.getY(), 1, "green");
        }
        for(unsigned int i = 0; i < positionsE2.size(); i++)
        {
            Geometry::Vec2Df pos = positionsE2[i];
            drawer.drawCircle(pos.getX(), pos.getY(), 1, "orange");

            Geometry::Vec2Df target = targets[i];
            drawer.drawCircle(target.getX(), target.getY(), 1, "purple");
        }
        drawer.end();

        std::cout << drawer.getContent().str();

    }

    void drawNavMesh(const AI::NavMesh::NavMesh& navMesh, Test::SvgDrawer& drawer)
    {
        const Graph::PlanarGraph& graph = navMesh.getGraph();
        //drawer.drawGraph(graph);
        const AI::NavMesh::NavMesh::PolygonsMap& polygonsMap = navMesh.getPolygonsMap();
        const AI::NavMesh::NavMesh::VerticesMap& verticesMap = navMesh.getVerticesMap();
        const Graph::PlanarGraph::NodeCollection& nodes = graph.getNodes();
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            const Graph::PlanarNode& node = nodes[i];
            const AI::NavMesh::NavMesh::VerticesIdsList& verticesIds = polygonsMap.at(node);
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
