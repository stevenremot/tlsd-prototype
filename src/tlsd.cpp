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

#include "Application/Boot/LuaLibBoot.h"
#include "Application/Boot/EventBoot.h"
#include "Application/Boot/GraphicsBoot.h"
#include "Application/Boot/UpdateBoot.h"
#include "Application/Boot/GenerationBoot.h"
#include "Application/Boot/CharacterBoot.h"
#include "Application/Boot/AnimationBoot.h"
#include "Application/Boot/AiBoot.h"
#include "Application/Boot/GameSceneBoot.h"
#include "Application/Boot/LuaInterpreterBoot.h"
#include "Application/Application.h"

int main()
{
    Event::EventManager eventManager;

    Application::Application app(42, eventManager);
    app
        .addBooter(new Application::LuaLibBoot(app))
        .addBooter(new Application::EventBoot(app, eventManager))
        .addBooter(new Application::GraphicsBoot(app))
        .addBooter(new Application::UpdateBoot(app))
        .addBooter(new Application::GenerationBoot(app))
        .addBooter(new Application::CharacterBoot(app))
        .addBooter(new Application::AnimationBoot(app))
        .addBooter(new Application::AiBoot(app))
        .addBooter(new Application::GameSceneBoot(app));

    app.start();

    return 0;
}
