# Documentation of the Lua API

## Random

The `random` module contains all basic primitives for random number
generation.

### Utility functions

#### `random.get_seed() -> number`

Return the seed representation as an integer.

### Number generator

#### `random.number_generator.new() -> number_generator`

Create a new number generator, initializing it with the game's seed.

#### `number_generator:get_uniform(min: number, max: number) -> number`

Return a random number between `min` and `max`, following a uniform distribution.

#### `number_generator:get_poisson(mean: integer > 0) -> integer > 0`

Return a number following a poisson distribution of the provided `mean`
