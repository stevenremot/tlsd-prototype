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

#ifndef LUA_STATE_H
#define LUA_STATE_H

#include <functional>
#include <exception>

#include <lua5.2/lua.hpp>

#include "../Core/Error.h"

namespace Lua
{
    /**
     * Class of lua thread derived from the base lua state.
     */
    class Thread
    {
    public:
        class CodeError: public Core::Error
        {
        public:
            CodeError(const std::string& errorMsg): Error(errorMsg) {}
        };

        typedef std::function<void ()> Closer;

        Thread(lua_State* L, Closer closer);
        Thread(Thread&& state);
        Thread(const Thread& state) = delete;
        Thread& operator=(const Thread& state) = delete;

        ~Thread();

        /**
         * Execute a code in the current thread
         */
        void doString(const std::string& code);

        void doString(const char* code);

        /**
         * Execute a body, passing the lua state to it.
         */
        void doWithState(std::function<void (lua_State*)> body)
        {
            body(L_);
        }

    private:
        lua_State* L_;
        Closer closer_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
