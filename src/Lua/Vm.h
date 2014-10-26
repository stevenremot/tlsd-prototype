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

#ifndef LUA_VM_H
#define LUA_VM_H

#include <memory>

#include <lua5.2/lua.hpp>

#include "Thread.h"

namespace Lua
{
    /**
     * Main entry point for the Lua machinery.
     *
     * Cannot be directly manipulated. You must create a new state
     * derived from the current one.
     */
    class Vm
    {
    public:
        Vm();
        Vm(const Vm& vm) = delete;
        Vm& operator=(const Vm& vm) = delete;
        ~Vm();

        /**
         * Create a new state.
         *
         * The state is derived from the main lua state.
         */
        std::unique_ptr<Thread> createThread();
    private:
        lua_State* L_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
