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

#include "AiBoot.h"

#include "Application.h"

namespace Application
{
    void AiBoot::start(Callback callback)
    {
        Threading::ConcurrentRessource<Ecs::World>& world =
            getApplication().getEcsWorld();

        aiSystem_ = new AI::AiSystem(world);
        sensorSystem_ = new AI::Sensor::SensorSystem(world);
        targetingSystem_ = new AI::Subsystem::TargetingSystem(world);

        std::vector<Threading::ThreadableInterface*> threadables;
        threadables.push_back(aiSystem_);
        threadables.push_back(sensorSystem_);
        threadables.push_back(targetingSystem_);

        setThread(new Threading::Thread(threadables, 20));
        getThread().start();
        callback();
    }

    void AiBoot::cleanUp()
    {
        delete targetingSystem_;
        delete sensorSystem_;
        delete aiSystem_;
    }
}
