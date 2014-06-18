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

#ifndef APPLICATION_GRAPHICS_BOOT_H
#define APPLICATION_GRAPHICS_BOOT_H

#include "BootInterface.h"
#include "../Ecs/World.h"

#include "../Graphics/Device.h"
#include "../Graphics/Render/Scene.h"
#include "../Input/IrrlichtInputReceiver.h"
#include "../Input/PlayerSystem.h"
#include "../Graphics/Render/RenderSystem.h"


namespace Application
{
    /**
     * Boots graphics thread.
     */
    class GraphicsBoot: public BootInterface
    {
    public:
        GraphicsBoot(Callback callback, Application& application):
            BootInterface(callback, application),
            device_(NULL),
            scene_(NULL),
            receiver_(NULL),
            playerSystem_(NULL),
            renderSystem_(NULL)
        {}

        virtual ~GraphicsBoot()
        {
            if (device_ != NULL)
            {
                delete scene_;
                delete receiver_;
                delete playerSystem_;
                delete renderSystem_;
                delete device_;
            }
        }

        virtual void start();
    private:
        Graphics::Device* device_;
        Graphics::Render::Scene* scene_;
        Input::IrrlichtInputReceiver* receiver_;
        Input::PlayerSystem* playerSystem_;
        Graphics::Render::RenderSystem* renderSystem_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
