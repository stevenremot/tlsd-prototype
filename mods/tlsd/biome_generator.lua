--------------------------------------------------------------------------------
-- Generator list --------------------------------------------------------------
--------------------------------------------------------------------------------

local default_generator = 'tlsd:default'
local generators = {}


local function get_configured_generator()
  if tlsd.config and tlsd.config.biomes and tlsd.config.biomes.generator
    and generators[tlsd.config.biomes.generator]
  then
    return generators[tlsd.config.biomes.generator]
  else
    return generators[default_generator]
  end
end

tlsd.biomes = {}

-- Define a new generator
--
-- NAME is a string to refer to this generator
--
-- GENERATOR is a function taking two argument : X and Y, and returning the biome name
-- at this position.
function tlsd.biomes.define_generator(name, generator)
  generators[name] = generator
end

-- Return the name of the biome that should be at position X, Y
function tlsd.biomes.get_biome_at(x, y)
  return get_configured_generator()(x, y)
end

--------------------------------------------------------------------------------
-- Plain biome generator -------------------------------------------------------
--------------------------------------------------------------------------------

local function plain_biome_generator(x, y)
  return 'plain'
end

tlsd.biomes.define_generator(
  'tlsd:plain',
  plain_biome_generator
)

--------------------------------------------------------------------------------
-- Default biome generator -----------------------------------------------------
--------------------------------------------------------------------------------

local humidity_noise = tlsd.random.perlin_noise.new()
local temperature_noise = tlsd.random.perlin_noise.new()

local function ensure_perlin_coef(x, y)
  if not humidity_noise:has_coefficient(x, y) then
    local number_generator = tlsd.random.number_generator.new(
      tlsd.random.get_seed() + x + y * y
    )

    humidity_noise:set_coefficient(
      x,
      y,
      number_generator:get_uniform(-1, 1),
      number_generator:get_uniform(-1, 1)
    )

    temperature_noise:set_coefficient(
      x,
      y,
      number_generator:get_uniform(-1, 1),
      number_generator:get_uniform(-1, 1)
    )
  end
end

local function get_grid_size()
  if tlsd.config and tlsd.config.biomes and tlsd.config.biomes.grid_size then
    return tlsd.config.biomes.grid_size
  else
    return 1
  end
end

local function perlin_noise_biome_generator(x, y)
  local grid_size = get_grid_size()

  x = x / grid_size - 0.5
  y = y / grid_size - 0.5

  local x1 = math.floor(x)
  local x2 = x1 + 1
  local y1 = math.floor(y)
  local y2 = y1 + 1

  ensure_perlin_coef(x1, y1)
  ensure_perlin_coef(x1, y2)
  ensure_perlin_coef(x2, y1)
  ensure_perlin_coef(x2, y2)

  local humidity_value = humidity_noise:compute_at(x, y)
  local temperature_value = temperature_noise:compute_at(x, y)

  if humidity_value >= 0 and temperature_value < 0 then
    return 'mountain'
  elseif humidity_value < 0 and temperature_value < 0 then
    return 'desert'
  else
    return 'plain'
  end
end

tlsd.biomes.define_generator(
  default_generator,
  perlin_noise_biome_generator
)
