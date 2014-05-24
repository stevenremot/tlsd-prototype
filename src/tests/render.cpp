#include "render.h"

#include <iostream>

#include "../Graphics/Device.h"
#include "../Graphics/Render/Scene.h"
#include "../Threading/Thread.h"

namespace RenderTest
{
    using Graphics::Render::Scene;
    using Graphics::Device;
    using Threading::ThreadableInterface;
    using Threading::Thread;

    void testThread()
    {
        Event::EventManager m;

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();

        Scene scene;
        reg.put(Graphics::Render::InitSceneEvent::TYPE, &scene);

        std::vector<ThreadableInterface*> threadables, threadables2;
        threadables.push_back(&device);
        threadables.push_back(&scene);
        threadables2.push_back(&m);
        Thread thread(threadables, 60);
        Thread thread2(threadables2, 5);
        thread.start();
        thread2.start();

        // wait for 4 seconds
        for (int i = 0; i < 20; i++)
        {
           Threading::sleep(0,200);
           std::cout << ".";
        }

        thread.stop();
        thread2.stop();
        std::cout << "thread stopped" << std::endl;

        // make sure the device object is deleted after the thread is stopped
        //Threading::sleep(1,0);
    }
}
