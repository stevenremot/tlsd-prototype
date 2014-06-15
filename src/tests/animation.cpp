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
#include "../Graphics/Render/AnimateActionEvent.h"
#include "../Character/MoveAction.h"
#include "../Character/StopAction.h"

using Graphics::Render::AnimateActionEvent;
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
        if (event.getType() == Input::MoveEvent::Type)
        {
            const Input::MoveEvent& me = static_cast<const Input::MoveEvent&>(event);

            if (me.getDirection() == Geometry::Vec2Df(1,0))
            {
                eventQueue_ << new AnimateActionEvent(0,Character::MoveAction::Type);
            }
            else if (me.getDirection() == Geometry::Vec2Df(0,0))
            {
                eventQueue_ << new AnimateActionEvent(0,Character::StopAction::Type);
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
        reg.put(Input::MoveEvent::Type, &l);

        Scene scene(m.getEventQueue());
        scene.registerListeners(reg);

        IrrlichtInputReceiver receiver(m.getEventQueue());
        reg.put(Input::InitInputEvent::TYPE, &receiver);

        RenderSystem rs(w, m.getEventQueue());
        reg.put(Ecs::ComponentCreatedEvent::TYPE, &rs);

        AnimationSystem as(w, m.getEventQueue());
        as.registerListeners(reg);

        std::vector<ThreadableInterface*> threadables, threadables2, threadables3;

        // Device, Scene and InputReceiver use irrlicht engine, so they should be in the same thread
        threadables.push_back(&device);
        threadables.push_back(&scene);
        threadables.push_back(&receiver);
        Thread thread(threadables, 60);

        threadables2.push_back(&m);
        Thread thread2(threadables2, 1000);

        threadables3.push_back(&as);
        Thread thread3(threadables3, 60);

        thread.start();
        thread2.start();
        thread3.start();

        AnimationMap animMap;
        animMap[Graphics::Render::Idle] = AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);
        animMap[Graphics::Render::Walk] = AnimationParameters(5.0f, true, Graphics::Render::NoAnimation);

        std::map<Character::Action::Type, AnimationType> animByAction;
        animByAction[Character::MoveAction::Type] = Graphics::Render::Walk;
        animByAction[Character::StopAction::Type] = Graphics::Render::Idle;

        std::string meshFile = "ninja.b3d";

        for (int i = 0; i < 15; i++)
        {
            Ecs::Entity e = w.createEntity();
            w.addComponent(e, new PositionComponent(Vec3Df(150+5*i,150,0)));
            w.addComponent(e, new RotationComponent(Vec3Df()));
            w.addComponent(e, new RenderableComponent(meshFile, ""));
            w.addComponent(e, new AnimationComponent(animMap, animByAction));
        }


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
