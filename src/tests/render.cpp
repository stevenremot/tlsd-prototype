#include "render.h"

#include <iostream>

#include "../Graphics/Device.h"
#include "../Threading/Thread.h"

namespace RenderTest
{
    using Graphics::Device;
    using Threading::ThreadableInterface;
    using Threading::Thread;

    void testThread()
    {
        Device device;

        std::vector<ThreadableInterface*> threadables;
        threadables.push_back(&device);
        Thread thread(threadables, 60);
        thread.start();

        // wait for 4 seconds
        for (int i = 0; i < 20; i++)
        {
           Threading::sleep(0,200);
        }
        thread.stop();
        std::cout << "thread stopped" << std::endl;

        // make sure the device object is deleted after the thread is stopped
        //Threading::sleep(1,0);
    }
}
