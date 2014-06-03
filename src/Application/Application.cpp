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

#include "Application.h"

#include "../Graphics/Device.h"
#include "../Graphics/Render/Scene.h"
#include "../Graphics/Render/RenderSystem.h"
#include "../Graphics/Render/RenderEvents.h"
#include "../Input/IrrlichtInputReceiver.h"
#include "../Input/Events.h"
#include "../Input/IrrlichtInputReceiver.h"
#include "../World/Generation/ChunkGenerationSystem.h"
#include "../Input/PlayerPositionChangedEvent.h"
#include "../Ecs/ComponentCreatedEvent.h"

namespace Application
{
    void Application::start()
    {
        setupEventThread();
        setupGraphicsThread();
        setupGenerationThread();

        eventThread_->start();
        graphicsThread_->start();
        generationThread_->start();

        for (unsigned int i = 0; i < 1000000; i++)
        {
            Threading::sleep(1, 0);
        }

        eventThread_->stop();
        graphicsThread_->stop();
        generationThread_->stop();
    }

    void Application::setupEventThread()
    {
        std::vector<Threading::ThreadableInterface*> eventThreadables;
        eventThreadables.push_back(&eventManager_);
        eventThread_ = new Threading::Thread(eventThreadables, 120);
    }

    void Application::setupGraphicsThread()
    {
        Event::ListenerRegister& reg = eventManager_.getListenerRegister();
        Event::EventQueue& queue = eventManager_.getEventQueue();

        Graphics::Device* dev = new Graphics::Device(queue);
        reg.put(Input::InputInitializedEvent::TYPE, dev);

        Graphics::Render::Scene* scene = new Graphics::Render::Scene;
        reg.put(Graphics::Render::InitSceneEvent::TYPE, scene);
        reg.put(Input::CameraEvent::TYPE, scene);
        reg.put(Input::MoveEvent::TYPE, scene);
        reg.put(Graphics::Render::RenderModel3DEvent::TYPE, scene);


        Input::IrrlichtInputReceiver* receiver =
            new Input::IrrlichtInputReceiver(queue);
        reg.put(Input::InitInputEvent::TYPE, receiver);


        std::vector<Threading::ThreadableInterface*> graphicsThreadables;
        graphicsThreadables.push_back(dev);
        graphicsThreadables.push_back(scene);
        graphicsThreadables.push_back(receiver);

        Graphics::Render::RenderSystem* rs =
            new Graphics::Render::RenderSystem(ecsWorld_, queue);
        reg.put(Ecs::ComponentCreatedEvent::TYPE, rs);

        graphicsThread_ = new Threading::Thread(graphicsThreadables, 60);
    }

    void Application::setupGenerationThread()
    {
        World::Generation::ChunkGenerator generator(world_, ecsWorld_, 42);

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                generator.generateChunk(i, j);
            }
        }

        // TODO Change world seed at each run :-)
        World::Generation::ChunkGenerationSystem* generation =
            new World::Generation::ChunkGenerationSystem(
                ecsWorld_,
                generator
            );

        generation->registerListeners(eventManager_.getListenerRegister());

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(generation);

        generationThread_ = new Threading::Thread(threadables, 1);
    }
}
