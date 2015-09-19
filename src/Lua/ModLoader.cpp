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

#include "ModLoader.h"

#include <iostream>

#include "../Core/DirIterator.h"

using Core::File;

namespace Lua
{
    ModLoader::ModLoader(const std::string& modDirectory):
        modDirectory_(modDirectory)
    {}

    void ModLoader::loadMods(Vm& vm) const
    {
        for (auto modDir : Core::DirIterator(modDirectory_))
        {
            auto initFile = File(File::joinPaths(modDir.getName(), "init.lua"));
            if (initFile.exists()) {
                std::cout << "Loading module " << initFile.getName() << "...";
                vm.doFile(initFile.getName());
                std::cout << "done" << std::endl;
            }
        }
    }
}
