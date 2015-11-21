Documentation of the Lua API
============================

Random
------

The `tlsd.random` module contains all basic primitives for random number
generation.


### Utility functions


#### `tlsd.random.get_seed() -> number`

Return the world seed representation as an integer.


### Number generator


#### `tlsd.random.number_generator.new([seed: integer > 0]) -> number_generator`

Create a new number generator, initializing it with the provided seed.

If no seed is provided, it uses the world seed.

Avoid injecting your own seeds for level generation, except if you
merge it with the world's one.

#### `number_generator:get_uniform(min: number, max: number) -> number`

Return a random number between `min` and `max`, following a uniform distribution.

#### `number_generator:get_poisson(mean: integer > 0) -> integer > 0`

Return a number following a poisson distribution of the provided `mean`


### Perlin noise


#### `tlsd.random.perlin_noise.new() -> perlin_noise`

Create a new perlin noise generator.

It contains no coefficient at startup, they must be added one by one later.

#### `perlin_noise:set_coefficient(posX: integer, posY: integer, coefX: number, coefY: number)`

Add a the perlin coefficient `(coefX, coefY)` at position `(posX, posY)`.

#### `perlin_noise.has_coefficient(posX: integer, posY: integer) -> boolean`

Return true if a coefficient has been set at position `(posX, posY)`.

#### `perlin_noise.compute_at(posX: number, posY: number) -> number`

Compute the Perlin noise value at position `(posX, posY)`.

If the coefficients around this position are not set, an error is
triggered.

Biomes
------

### `tlsd.biome.define_generator(name: string, generator (x: number, y: number) -> string)`

Define a new generator.

`name` is the name of the generator, to set it in the configuration.

`generator` is a function taking a 2D world coordinate and returning
the name of the biome at this position.

### `tlsd.biomes.get_biome_at(x: number, y: number) -> string`

Return the name of the biome at position `(x, y)`.

If a biome generator is in the configuration key
`tlsd.config.biomes.generator`, it will be used to determine the
biome. Otherwise, it will be `tlsd:default` generator.
