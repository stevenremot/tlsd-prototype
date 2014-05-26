#include "render.h"

#include <iostream>

#include "../Graphics/Device.h"
#include "../Graphics/Render/Scene.h"
#include "../Threading/Thread.h"

#include "../Input/Events.h"
#include "../Input/IrrlichtInputReceiver.h"

namespace RenderTest
{
    using Graphics::Render::Scene;
    using Graphics::Device;
    using Threading::ThreadableInterface;
    using Threading::Thread;
    using Input::IrrlichtInputReceiver;

    void DummyInputListener::call(const Event::Event& event)
    {
        std::cout << static_cast<const Input::MoveEvent&>(event).getDirection() << std::endl;
    }

    void testThread()
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
        threadables2.push_back(&m);
        Thread thread(threadables, 60);
        Thread thread2(threadables2, 120);
        thread.start();
        thread2.start();

        // wait for 4 seconds
        for (int i = 0; i < 200; i++)
        {
           Threading::sleep(0,40);
        }

        thread.stop();
        thread2.stop();
        std::cout << "thread stopped" << std::endl;

        // make sure the device object is deleted after the thread is stopped
        //Threading::sleep(1,0);
    }

    void testCamera()
    {
        // TODO : Solve the synchronization issues where the eventManager and the other objects are in different threads

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
