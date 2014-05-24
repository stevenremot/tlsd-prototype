import os

env = Environment(Env=os.environ, tools=['mingw'])

env.Append(CXXFLAGS = ["-Wall"])

if ARGUMENTS.get("debug", 0):
    env.Append(CXXFLAGS = ["-g"])


if ARGUMENTS.get("clang", 0):
    env.Replace(CC = "clang",
                CXX = "clang++")

libs = []
if env['PLATFORM'] == 'win32':
	libs = ["pthreadGC2","lemon","ws2_32"]
elif env['PLATFORM'] == 'posix':
	libs = ["pthread","emon","nsl"]
					
env.Program('program', Glob('src/*.cpp') + Glob('src/**/*.cpp'), LIBS=libs)

# Emacs local variables
# Local variables:
# mode: python
# End:
