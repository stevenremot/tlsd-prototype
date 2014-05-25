env = Environment()

env.Append(CXXFLAGS = ["-Wall"])

if ARGUMENTS.get("debug", 0):
    env.Append(CXXFLAGS = ["-g"])


if ARGUMENTS.get("clang", 0):
    env.Replace(CC = "clang",
                CXX = "clang++")

libs = []
if env['PLATFORM'] == 'win32':
	libs = ["pthreadGC2","lemon","Irrlicht"]
elif env['PLATFORM'] == 'posix':
	libs = ["pthread","emon","Irrlicht","X11"]
					
env.Program('program', Glob('src/*.cpp') + Glob('src/*/*.cpp') + Glob('src/*/*/*.cpp'), LIBS=libs)

# Emacs local variables
# Local variables:
# mode: python
# End:
