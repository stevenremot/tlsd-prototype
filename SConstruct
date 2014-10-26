import os

# Library names for each system
# "default" is the key of libraries that must be linked for any compiler
# "pthread" is the name of the pthread lib on the current system
#           (gcc needs it to be linked explicitly)
libs_path = {
    "win32": {
        "default": ["Irrlicht"],
        "pthread": ["pthreadGC2"]
    },
    "posix": {
        "default": ["Irrlicht", "X11"],
        "pthread": ["pthread"]
    }
}


# Setup per compiler
# This sets some variables on the environment and returns the
# libraries required for the compiler
def setup_gcc(env):
    """Setup environment for gcc

    Return the new environment, and the set of libraries to link for
    it.

    """
    env.Append(
        CXXFLAGS="-pthread"
    )

    return env, ["default", "pthread"]


def setup_clang(env):
    """Setup environment for clang

    Return the new environment, and the set of libraries to link for
    it.

    """
    env.Replace(
        CC="clang",
        CXX="clang++"
    )
    return env, ["default"]


# Environment creation
env = Environment(ENV=os.environ)

# Common settings
env.Append(
    CXXFLAGS=["-Wall", "-std=gnu++11"],
    LINKFLAGS=["-std=gnu++11"],
    CPPPATH=['libs']
)

# Build environment arguments
if ARGUMENTS.get("debug", 0):
    env.Append(CXXFLAGS=["-g"])
else:
    env.Append(CXXFLAGS=["-O3"])

# Setup per compiler and system
func = setup_clang if ARGUMENTS.get("clang", False) else setup_gcc
env, lib_keys = func(env)

platform = env['PLATFORM']
libs = [name for key in lib_keys for name in libs_path[platform][key]]

config = Configure(env)
if config.CheckLib('lua52'):
    libs.append('lua52')
elif config.CheckLib('lua5.2'):
    libs.append('lua5.2')
else:
    print 'liblua not found.'
    exit()

# Source definition
sources = Glob('src/*/*.cpp') + Glob('src/*/*/*.cpp') + Glob('src/*/*/*/*.cpp')
includedLibs = Glob('libs/*.cpp')
main = Glob('src/main.cpp')

# Program definition
env.Program('program', sources + includedLibs + main, LIBS=libs)

# Emacs local variables
# Local variables:
# mode: python
# End:
