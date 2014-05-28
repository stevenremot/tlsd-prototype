#include "render.h"

#include <iostream>

#include "../Graphics/Device.h"
#include "../Graphics/Render/Scene.h"
#include "../Graphics/Render/RenderSystem.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/Events.h"
#include "../Graphics/Render/ModelUtils.h"

#include "../Geometry/PositionComponent.h"

#include "../Threading/Thread.h"

#include "../Input/Events.h"
#include "../Input/IrrlichtInputReceiver.h"

#include "../Random/NumberGenerator.h"

#include "../Ecs/ComponentCreatedEvent.h"

using Graphics::Render::Scene;
using Graphics::Device;
using Threading::ThreadableInterface;
using Threading::Thread;
using Input::IrrlichtInputReceiver;
using Geometry::PositionComponent;
using Graphics::Render::RenderableComponent;
using Graphics::Render::RenderSystem;

namespace RenderTest
{
    void DummyInputListener::call(const Event::Event& event)
    {
        std::cout << static_cast<const Input::MoveEvent&>(event).getDirection() << std::endl;
    }

    void testThread(int durationInSeconds)
    {
        Event::EventManager m;

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();
        reg.put(Input::InputInitializedEvent::TYPE, &device);

        Scene scene;
        reg.put(Graphics::Render::InitSceneEvent::TYPE, &scene);
        reg.put(Input::CameraEvent::TYPE, &scene);
        reg.put(Input::MoveEvent::TYPE, &scene);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::TYPE, &receiver);

        //DummyInputListener inputListener;
        //reg.put(Input::MoveEvent::TYPE, &inputListener);

        std::vector<ThreadableInterface*> threadables, threadables2;
        threadables.push_back(&device);
        threadables.push_back(&scene);
        threadables.push_back(&receiver);
        threadables2.push_back(&m);
        Thread thread(threadables, 60);
        Thread thread2(threadables2, 200);
        thread.start();
        thread2.start();

        int imax = durationInSeconds * 10;
        for (int i = 0; i < imax; i++)
        {
           Threading::sleep(0,100);
        }

        thread.stop();
        thread2.stop();
        std::cout << "thread stopped" << std::endl;
    }

    void testRenderSystem(int durationInSeconds)
    {
        Event::EventManager m;
        Ecs::World w(m.getEventQueue());

        Random::NumberGenerator rng(1);

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();
        reg.put(Input::InputInitializedEvent::TYPE, &device);

        Scene scene;
        reg.put(Graphics::Render::InitSceneEvent::TYPE, &scene);
        reg.put(Input::CameraEvent::TYPE, &scene);
        reg.put(Input::MoveEvent::TYPE, &scene);
        reg.put(Graphics::Render::RenderMeshFileEvent::TYPE, &scene);
        reg.put(Graphics::Render::RenderModel3DEvent::TYPE, &scene);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::TYPE, &receiver);

        RenderSystem rs(w, m.getEventQueue());
        reg.put(Ecs::ComponentCreatedEvent::TYPE, &rs);

        std::vector<ThreadableInterface*> threadables, threadables2;

        // Device, Scene and InputReceiver use irrlicht engine, so they should be in the same thread
        threadables.push_back(&device);
        threadables.push_back(&scene);
        threadables.push_back(&receiver);
        Thread thread(threadables, 60);

        threadables2.push_back(&m);
        Thread thread2(threadables2, 200);

        thread.start();
        thread2.start();

        Graphics::Render::Model3D cube = Graphics::Render::createPrettyCubeModel();
        std::string meshFile = "ninja.b3d";

        int imax = durationInSeconds * 1;
        for (int i = 0; i < imax; i++)
        {
            Ecs::Entity e = w.createEntity(i);
            w.addComponent(e, new PositionComponent(Vec3Df(rng.getUniform(-5, 5), rng.getUniform(-5, 5), 0)));
            if (i % 2)
                w.addComponent(e, new RenderableComponent(meshFile, ""));
            else
                w.addComponent(e, new RenderableComponent(cube));

            Threading::sleep(1,0);
        }

        thread.stop();
        thread2.stop();
        std::cout << "thread stopped" << std::endl;


    }



    void testCamera()
    {
        Event::EventManager m;

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();
        reg.put(Input::InputInitializedEvent::TYPE, &device);

        Scene scene;
        reg.put(Graphics::Render::InitSceneEvent::TYPE, &scene);
        reg.put(Input::CameraEvent::TYPE, &scene);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::TYPE, &receiver);

        DummyInputListener inputListener;
        reg.put(Input::MoveEvent::TYPE, &inputListener);

        std::vector<ThreadableInterface*> threadables, threadables2;
        threadables.push_back(&device);
        threadables.push_back(&scene);
        threadables.push_back(&receiver);
        threadables.push_back(&m);
        Thread thread(threadables, 60);
        thread.start();

        // wait for 20 seconds
        for (int i = 0; i < 200; i++)
        {
           Threading::sleep(0,20);
        }

        thread.stop();
        std::cout << "thread stopped" << std::endl;

    }
}
