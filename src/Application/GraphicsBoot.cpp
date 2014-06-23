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

#include "GraphicsBoot.h"
#include "Application.h"

#include "../Ecs/ComponentCreatedEvent.h"
#include "../Graphics/CloseDeviceEvent.h"
#include "../Graphics/Render/RenderEvents.h"
#include "../Input/Events.h"

namespace Application
{
    void GraphicsBoot::start()
    {
        Threading::ConcurrentRessource<Ecs::World>& ecsWorld =
            getApplication().getEcsWorld();
        Event::ListenerRegister& reg = getApplication().getEventManager().getListenerRegister();
        Event::EventQueue& queue = getApplication().getEventManager().getEventQueue();

        reg.put(Graphics::CloseDeviceEvent::Type, &getApplication());

        device_ = new Graphics::Device(queue);
        reg.put(Input::InputInitializedEvent::Type, device_);

        scene_ = new Graphics::Render::Scene(queue);
        scene_->registerListeners(reg);

        receiver_ = new Input::IrrlichtInputReceiver(queue);
        reg.put(Input::InitInputEvent::Type, receiver_);

        playerSystem_ = new Input::PlayerSystem(ecsWorld, queue);
        playerSystem_->registerListeners(reg);

        std::vector<Threading::ThreadableInterface*> graphicsThreadables;
        graphicsThreadables.push_back(device_);
        graphicsThreadables.push_back(scene_);
        graphicsThreadables.push_back(receiver_);
        graphicsThreadables.push_back(playerSystem_);

        renderSystem_ = new Graphics::Render::RenderSystem(ecsWorld, queue);
        reg.put(Ecs::ComponentCreatedEvent::Type, renderSystem_);

        setThread(new Threading::Thread(graphicsThreadables, 60));
        getThread().start();
        finishBoot();
    }
}
