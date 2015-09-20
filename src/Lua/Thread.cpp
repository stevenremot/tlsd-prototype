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

#include "Thread.h"

#include <string>

namespace Lua
{
    Thread::Thread(lua_State* L, Thread::Closer closer):
        L_(L),
        closer_(closer)
    {
    }

    Thread::Thread(Thread&& state):
        L_(state.L_),
        closer_(state.closer_)
    {
        state.L_ = nullptr;
    }

    Thread::~Thread()
    {
        if (L_ != nullptr)
        {
            closer_();
        }
    }

    void Thread::doString(const std::string& code)
    {
        doString(code.c_str());
    }

    void Thread::doString(const char* code)
    {
        int error = luaL_loadstring(L_, code) || lua_pcall(L_, 0, 0, 0);
        if (error)
        {
            std::string s = lua_tostring(L_, -1);
            lua_pop(L_, 1);
            throw CodeError(s);
        }
    }
}
