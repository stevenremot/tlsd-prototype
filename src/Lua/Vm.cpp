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

#include "Vm.h"

namespace Lua
{
    Vm::Vm(): L_(luaL_newstate())
    {
        luaL_openlibs(L_);
    }

    Vm::~Vm()
    {
        lua_close(L_);
    }

    std::unique_ptr<Thread> Vm::createThread()
    {
        lua_State* thread = lua_newthread(L_);
        int ref = luaL_ref(L_, LUA_REGISTRYINDEX);
        return std::unique_ptr<Thread>(
            new Thread(
                thread,
                [this, ref] () { luaL_unref(this->L_, LUA_REGISTRYINDEX, ref); }
            )
        );
    }
}
