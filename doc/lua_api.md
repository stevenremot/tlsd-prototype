# Documentation of the Lua API

## Random

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

#### `tlsd.number_generator:get_uniform(min: number, max: number) -> number`

Return a random number between `min` and `max`, following a uniform distribution.

#### `tlsd.number_generator:get_poisson(mean: integer > 0) -> integer > 0`

Return a number following a poisson distribution of the provided `mean`
