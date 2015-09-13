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

#ifndef APPLICATION_GENERATION_BOOT_H
#define APPLICATION_GENERATION_BOOT_H

#include "ThreadBoot.h"
#include "../World/Generation/ChunkGenerationSystem.h"

namespace Application
{
    class GenerationBoot: public ThreadBoot
    {
    public:
        GenerationBoot(Application& application):
            ThreadBoot(application),
            generationSystem_(NULL)
        {}

        virtual void start(Callback callback);

    protected:

        virtual void cleanUp();

    private:
        World::Generation::ChunkGenerationSystem* generationSystem_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
