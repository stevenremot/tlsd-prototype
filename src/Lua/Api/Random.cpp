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

#include <iostream>

#include "Random.h"

using Random::NumberGenerator;

static const char* NUMBER_GENERATOR_METATABLE = "Tlsd.random.number_generator";

// Utility functions

static Random::Seed getSeed(lua_State* L)
{
    return *((Random::Seed*)lua_touserdata(L, lua_upvalueindex(1)));
}

static int returnSeed(lua_State* L)
{
    lua_pushinteger(L, getSeed(L));
    return 1;
}

// Number generator creation

static int createNumberGenerator(lua_State* L)
{
    NumberGenerator* generator = static_cast<NumberGenerator*>(lua_newuserdata(L, sizeof(NumberGenerator)));
    *generator = NumberGenerator(getSeed(L));
    luaL_getmetatable(L, NUMBER_GENERATOR_METATABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static NumberGenerator& getNumberGeneratorArg(lua_State* L, int narg = 1)
{
    return *static_cast<NumberGenerator*>(luaL_checkudata(L, narg, NUMBER_GENERATOR_METATABLE));
}

static int getNumberGeneratorUniform(lua_State* L)
{
    NumberGenerator& generator = getNumberGeneratorArg(L);
    float min = luaL_checknumber(L, 2);
    float max = luaL_checknumber(L, 3);
    lua_pushnumber(L, generator.getUniform(min, max));
    return 1;
}

static int getNumberGeneratorPoisson(lua_State* L)
{
    NumberGenerator& generator = getNumberGeneratorArg(L);
    int mean = luaL_checkint(L, 2);
    luaL_argcheck(L, mean >= 0, 2, "Poisson mean must be positive");
    lua_pushnumber(L, generator.getPoisson(static_cast<unsigned int>(mean)));
    return 1;
}

// Setup function

static const struct luaL_Reg randomLib [] = {
    {"get_seed", returnSeed},
    {NULL, NULL}
};

static const struct luaL_Reg randomGenLib [] = {
    {"new", createNumberGenerator},
    {NULL, NULL}
};

static const struct luaL_Reg randomGenObjLib [] = {
    {"get_uniform", getNumberGeneratorUniform},
    {"get_poisson", getNumberGeneratorPoisson},
    {NULL, NULL}
};

void Lua::Api::Random::setup(Lua::Vm& vm, const ::Random::Seed& seed)
{
    vm.doWithState(
        [seed](lua_State*const L) {
            // Creating number generator metatable
            luaL_newmetatable(L, NUMBER_GENERATOR_METATABLE);

            lua_pushvalue(L, -1);
            lua_setfield(L, -2, "__index");

            luaL_setfuncs(L, randomGenObjLib, 0);

            // Creating random lib
            luaL_newlibtable(L, randomLib);

            auto luaSeed = (::Random::Seed*)lua_newuserdata(L, sizeof(seed));
            *luaSeed = seed;

            luaL_setfuncs(L, randomLib, 1);

            // Creating number generator lib
            luaL_newlibtable(L, randomGenLib);

            luaSeed = (::Random::Seed*)lua_newuserdata(L, sizeof(seed));
            *luaSeed = seed;

            luaL_setfuncs(L, randomGenLib, 1);
            lua_setfield(L, -2, "number_generator");

            // Registering lib
            lua_setglobal(L, "random");
        }
    );
}
