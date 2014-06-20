env = Environment()

env.Append(CXXFLAGS = ["-Wall"])

if ARGUMENTS.get("debug", 0):
    env.Append(CXXFLAGS = ["-g"])


if ARGUMENTS.get("clang", 0):
    env.Replace(CC = "clang",
                CXX = "clang++")

libs = []
if env['PLATFORM'] == 'win32':
	libs = ["pthreadGC2","lemon"]
elif env['PLATFORM'] == 'posix':
    libs = ["pthread","emon"]

env.Append(CPPPATH=['libs'])

sources = Glob('src/*/*.cpp') + Glob('src/*/*/*.cpp') + Glob('src/*/*/*/*.cpp')
includedLibs = Glob('libs/*.cpp')
main = Glob('src/main.cpp')

env.Program('program', sources + includedLibs + main, LIBS=libs)

# Emacs local variables
# Local variables:
# mode: python
# End:
