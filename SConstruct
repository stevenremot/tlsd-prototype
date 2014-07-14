import os

env = Environment()
env.Append(
    CXXFLAGS = ["-Wall", "-std=c++11"],
    LINKFLAGS = ["-pthread", "-std=c++11"]
)

if ARGUMENTS.get("debug", 0):
    env.Append(CXXFLAGS = ["-g"])
else:
    env.Append(CXXFLAGS = ["-O3"])

if ARGUMENTS.get("clang", 0):
    env.Replace(CC = "clang",
                CXX = "clang++")

libs = []
if env['PLATFORM'] == 'win32':
	env = Environment(Env=os.environ, tools=['mingw'])
	libs = ["Irrlicht"]
elif env['PLATFORM'] == 'posix':
	libs = ["Irrlicht","X11"]

env.Append(CPPPATH=['libs'])

sources = Glob('src/*/*.cpp') + Glob('src/*/*/*.cpp') + Glob('src/*/*/*/*.cpp')
includedLibs = Glob('libs/*.cpp')
main = Glob('src/main.cpp')

env.Program('program', sources + includedLibs + main, LIBS=libs)

# Emacs local variables
# Local variables:
# mode: python
# End:
