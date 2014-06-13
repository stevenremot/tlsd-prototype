#include "animation.h"

#include <iostream>
#include "../Input/IrrlichtInputReceiver.h"
#include "../Input/Events.h"
#include "../Graphics/Render/RenderSystem.h"
#include "../Graphics/Render/AnimationSystem.h"
#include "../Graphics/Device.h"
#include "../Graphics/Render/Scene.h"
#include "../Graphics/Render/RenderEvents.h"
#include "../Graphics/Render/AnimationEvents.h"
#include "../Threading/Thread.h"
#include "../Ecs/ComponentCreatedEvent.h"
#include "../Geometry/PositionComponent.h"
#include "../Geometry/RotationComponent.h"
#include "../Graphics/Render/RenderableComponent.h"
#include "../Graphics/Render/AnimationComponent.h"

using Graphics::Render::DummyActionEvent;
using Graphics::Render::Scene;
using Graphics::Device;
using Graphics::Render::RenderSystem;
using Graphics::Render::AnimationSystem;
using Input::IrrlichtInputReceiver;
using Threading::ThreadableInterface;
using Threading::Thread;
using Graphics::Render::AnimationType;
using Graphics::Render::AnimationMap;
using Graphics::Render::AnimationParameters;
using Geometry::PositionComponent;
using Geometry::RotationComponent;
using Graphics::Render::RenderableComponent;
using Graphics::Render::AnimationComponent;

namespace AnimationTest
{
    void DummyInputListener::call(const Event::Event& event)
    {
        if (event.getType() == Input::MoveEvent::TYPE)
        {
            const Input::MoveEvent& me = static_cast<const Input::MoveEvent&>(event);

            if (me.getDirection() == Geometry::Vec2Df(1,0))
            {
                eventQueue_ << new DummyActionEvent(0,1); // entity 0, action 1
            }
        }
    }

    void testAnimation()
    {
        Event::EventManager m;
        Ecs::World w(m.getEventQueue());

        Device device(m.getEventQueue());
        Event::ListenerRegister& reg = m.getListenerRegister();
        reg.put(Input::InputInitializedEvent::TYPE, &device);

        DummyInputListener l(m.getEventQueue());
        reg.put(Input::MoveEvent::TYPE, &l);

        Scene scene(m.getEventQueue());
        scene.registerListeners(reg);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::TYPE, &receiver);

        RenderSystem rs(w, m.getEventQueue());
        reg.put(Ecs::ComponentCreatedEvent::TYPE, &rs);

        AnimationSystem as(w, m.getEventQueue());
        reg.put(Ecs::ComponentCreatedEvent::TYPE, &as);
        reg.put(Graphics::Render::DummyActionEvent::TYPE, &as);

        std::vector<ThreadableInterface*> threadables, threadables2;

        // Device, Scene and InputReceiver use irrlicht engine, so they should be in the same thread
        threadables.push_back(&device);
        threadables.push_back(&scene);
        threadables.push_back(&receiver);
        threadables.push_back(&as);
        Thread thread(threadables, 60);

        threadables2.push_back(&m);
        Thread thread2(threadables2, 200);

        thread.start();
        thread2.start();

        AnimationMap animMap;
        animMap[Graphics::Render::Idle] = AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
        animMap[Graphics::Render::Walk] = AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);

        std::map<unsigned int, AnimationType> animByAction;
        animByAction[0] = Graphics::Render::Idle;
        animByAction[1] = Graphics::Render::Walk;

        std::string meshFile = "ninja.b3d";
        Ecs::Entity e = w.createEntity(0);
        w.addComponent(e, new PositionComponent(Vec3Df()));
        w.addComponent(e, new RotationComponent(Vec3Df()));
        w.addComponent(e, new RenderableComponent(meshFile, ""));
        w.addComponent(e, new AnimationComponent(animMap, animByAction));

        int imax = 20 * 1;
        for (int i = 0; i < imax; i++)
        {
            Threading::sleep(1,0);
        }

        thread.stop();
        thread2.stop();
        std::cout << "thread stopped" << std::endl;
    }
}
