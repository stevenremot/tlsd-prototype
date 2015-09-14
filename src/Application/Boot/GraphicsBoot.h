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

#include "ThreadBoot.h"
#include "../../Ecs/World.h"

#include "../../Graphics/Device.h"
#include "../../Graphics/Render/Scene.h"
#include "../../Graphics/Render/RenderSystem.h"
#include "../../Graphics/Gui/HudSystem.h"
#include "../../Input/IrrlichtInputReceiver.h"
#include "../../Input/PlayerSystem.h"


namespace Application
{
    /**
     * Boots graphics thread.
     */
    class GraphicsBoot: public ThreadBoot
    {
    public:
        GraphicsBoot(Application& application):
            ThreadBoot(application),
            device_(NULL),
            scene_(NULL),
            receiver_(NULL),
            playerSystem_(NULL),
            renderSystem_(NULL),
            hudSystem_(NULL)
        {}


        virtual void start(Callback callback);

    protected:

        virtual void cleanUp();

    private:
        Graphics::Device* device_;
        Graphics::Render::Scene* scene_;
        Input::IrrlichtInputReceiver* receiver_;
        Input::PlayerSystem* playerSystem_;
        Graphics::Render::RenderSystem* renderSystem_;
        Graphics::Gui::HudSystem* hudSystem_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
