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

#include "render.h"

#include <iostream>

#include "../Graphics/Device.h"
#include "../Graphics/CloseDeviceEvent.h"
#include "../Graphics/Render/Scene.h"
#include "../Graphics/Render/RenderSystem.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/RenderEvents.h"
#include "../Graphics/Render/ModelUtils.h"

#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"

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
using Geometry::RotationComponent;
using Geometry::Vec3Df;
using Graphics::Render::RenderableComponent;
using Graphics::Render::RenderSystem;

namespace RenderTest
{
    void DummyInputListener::call(const Event::Event& event)
    {
        std::cout << static_cast<const Input::MoveEvent&>(event).getDirection() << std::endl;
    }

    void CloseDeviceListener::call(const Event::Event& event)
    {
        closed_ = true;
    }

    void testThread(int durationInSeconds)
    {
        Event::EventManager m;

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();
        reg.put(Input::InputInitializedEvent::Type, &device);

        Scene scene(m.getEventQueue());
        scene.registerListeners(reg);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::Type, &receiver);

        //DummyInputListener inputListener;
        //reg.put(Input::MoveEvent::Type, &inputListener);

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
            Threading::sleep(Core::makeDurationMillis(100));
        }

        thread.stop();
        thread2.stop();
        std::cout << "thread stopped" << std::endl;
    }

    void testRenderSystem(int durationInSeconds)
    {
        Event::EventManager m;
        Threading::ConcurrentRessource<Ecs::World> w(new Ecs::World(m.getEventQueue()));

        Random::NumberGenerator rng(1);

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();
        reg.put(Input::InputInitializedEvent::Type, &device);

        Scene scene(m.getEventQueue());
        scene.registerListeners(reg);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::Type, &receiver);

        RenderSystem rs(w, m.getEventQueue());
        reg.put(Ecs::ComponentCreatedEvent::Type, &rs);

        CloseDeviceListener cdl;
        reg.put(Graphics::CloseDeviceEvent::Type, &cdl);

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

        int imax = durationInSeconds;
        for (int i = 0; i < imax && !cdl.closed_; i++)
        {
            {
                Threading::ConcurrentWriter<Ecs::World> ww = w.getWriter();
                Ecs::Entity e = ww->createEntity(i);
                ww->addComponent(e, new PositionComponent(Vec3Df(rng.getUniform(-5, 5), rng.getUniform(-5, 5), 0)));
                ww->addComponent(e, new RotationComponent(Vec3Df(0, 0, rng.getUniform(0, 360))));
                if (i % 2)
                    ww->addComponent(e, new RenderableComponent(meshFile, ""));
                else
                    ww->addComponent(e, new RenderableComponent(cube));
            }

            Threading::sleep(Core::makeDurationMillis(1000));
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
        reg.put(Input::InputInitializedEvent::Type, &device);

        Scene scene(m.getEventQueue());
        reg.put(Graphics::Render::InitSceneEvent::Type, &scene);
        reg.put(Input::CameraEvent::Type, &scene);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::Type, &receiver);

        DummyInputListener inputListener;
        reg.put(Input::MoveEvent::Type, &inputListener);

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
            Threading::sleep(Core::makeDurationMillis(20));
        }

        thread.stop();
        std::cout << "thread stopped" << std::endl;

    }
}
