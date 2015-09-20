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
#include "../../Random/PerlinNoise.h"

using Random::NumberGenerator;
using Random::PerlinNoise;

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

// Number generator

static const char* NUMBER_GENERATOR_METATABLE = "Tlsd.random.number_generator";

static int createNumberGenerator(lua_State* L)
{
    int top = lua_gettop(L);

    Random::Seed seed = (top == 0)
        ? getSeed(L)
        : static_cast<Random::Seed>(luaL_checkint(L, 1));

    NumberGenerator* generator = static_cast<NumberGenerator*>(lua_newuserdata(L, sizeof(NumberGenerator)));

    *generator = NumberGenerator(seed);
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

// Perlin noise

static const char* PERLIN_NOISE_METATABLE = "Tlsd.random;perlin_noise";

static int createPerlinNoise(lua_State* L)
{
    PerlinNoise** noise = static_cast<PerlinNoise**>(lua_newuserdata(L, sizeof(PerlinNoise*)));
    *noise = new PerlinNoise();
    luaL_getmetatable(L, PERLIN_NOISE_METATABLE);
    lua_setmetatable(L, -2);
    return 1;
}

static PerlinNoise& getPerlinNoiseArg(lua_State* L, int narg = 1)
{
    return **static_cast<PerlinNoise**>(luaL_checkudata(L, narg, PERLIN_NOISE_METATABLE));
}

static int destroyPerlinNoise(lua_State* L)
{
    delete *static_cast<PerlinNoise**>(luaL_checkudata(L, 1, PERLIN_NOISE_METATABLE));
    return 0;
}

static int setPerlinNoiseCoeff(lua_State* L)
{
    PerlinNoise& noise = getPerlinNoiseArg(L);
    int posX = luaL_checkint(L, 2);
    int posY = luaL_checkint(L, 3);
    float coeffX = luaL_checknumber(L, 4);
    float coeffY = luaL_checknumber(L, 5);

    noise.setCoefficient(
        Geometry::Vec2Di(posX, posY),
        Geometry::Vec2Df(coeffX, coeffY)
    );

    return 0;
}

static int hasPerlinNoiseCoeff(lua_State* L)
{
    PerlinNoise& noise = getPerlinNoiseArg(L);
    int posX = luaL_checkint(L, 2);
    int posY = luaL_checkint(L, 3);

    if (noise.hasCoefficient(Geometry::Vec2Di(posX, posY)))
    {
        lua_pushboolean(L, 1);
    }
    else
    {
        lua_pushboolean(L, 0);
    }

    return 1;
}

static int computePerlinNoiseAt(lua_State* L)
{
    PerlinNoise& noise = getPerlinNoiseArg(L);
    float posX = luaL_checknumber(L, 2);
    float posY = luaL_checknumber(L, 3);

    int result = 1;

    try
    {
        lua_pushnumber(L, noise.computeAt(Geometry::Vec2Df(posX, posY)));

    }
    catch (const PerlinNoise::UninitializedCoefficientsException& e)
    {
        luaL_error(L, e.what());
        result = 0;
    }

    return result;
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

static const struct luaL_Reg perlinNoiseLib [] = {
    {"new", createPerlinNoise},
    {NULL, NULL}
};

static const struct luaL_Reg perlinNoiseObjLib [] = {
    {"set_coefficient", setPerlinNoiseCoeff},
    {"has_coefficient", hasPerlinNoiseCoeff},
    {"compute_at", computePerlinNoiseAt},
    {"__gc", destroyPerlinNoise},
    {NULL, NULL}
};

static void setupNumberGenerator(lua_State* L, const ::Random::Seed& seed)
{
    // Creating number generator metatable
    luaL_newmetatable(L, NUMBER_GENERATOR_METATABLE);

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    luaL_setfuncs(L, randomGenObjLib, 0);
    lua_pop(L, 1);

    // Creating number generator lib
    luaL_newlibtable(L, randomGenLib);

    auto luaSeed = (::Random::Seed*)lua_newuserdata(L, sizeof(seed));
    *luaSeed = seed;

    luaL_setfuncs(L, randomGenLib, 1);
    lua_setfield(L, -2, "number_generator");
}

static void setupPerlinNoise(lua_State* L)
{
    // Creating Perlin noise metatable
    luaL_newmetatable(L, PERLIN_NOISE_METATABLE);

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    luaL_setfuncs(L, perlinNoiseObjLib, 0);
    lua_pop(L, 1);

    // Creating perlin noise lib
    luaL_newlibtable(L, perlinNoiseLib);

    luaL_setfuncs(L, perlinNoiseLib, 0);
    lua_setfield(L, -2, "perlin_noise");
}

void Lua::Api::Random::setup(Lua::Vm& vm, const ::Random::Seed& seed)
{
    vm.doWithState(
        [seed](lua_State*const L) {
            // Creating random lib
            luaL_newlibtable(L, randomLib);

            auto luaSeed = (::Random::Seed*)lua_newuserdata(L, sizeof(seed));
            *luaSeed = seed;

            luaL_setfuncs(L, randomLib, 1);

            setupNumberGenerator(L, seed);
            setupPerlinNoise(L);

            // Registering lib
            lua_getglobal(L, "tlsd");
            lua_insert(L, -2);
            lua_setfield(L, -2, "random");
        }
    );
}
