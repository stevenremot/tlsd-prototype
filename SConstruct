import os

env = Environment(ENV = os.environ)
env.Append(
    CXXFLAGS = ["-Wall", "-pthread", "-std=gnu++11"],
    LINKFLAGS = ["-std=gnu++11"]
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
	env.Replace(tools=['mingw'])
	libs = ["pthreadGC2", "Irrlicht"]
elif env['PLATFORM'] == 'posix':
	libs = ["pthread", "Irrlicht", "X11"]

env.Append(CPPPATH=['libs'])

sources = Glob('src/*/*.cpp') + Glob('src/*/*/*.cpp') + Glob('src/*/*/*/*.cpp')
includedLibs = Glob('libs/*.cpp')
main = Glob('src/main.cpp')

env.Program('program', sources + includedLibs + main, LIBS=libs)

# Emacs local variables
# Local variables:
# mode: python
# End:
