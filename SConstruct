env = Environment()

env.Append(CXXFLAGS = ["-Wall"])

if ARGUMENTS.get("debug", 0):
    env.Append(CXXFLAGS = ["-g"])


if ARGUMENTS.get("clang", 0):
    env.Replace(CC = "clang",
                CXX = "clang++")

env.Program('program', Glob('src/*.cpp') + Glob('src/**/*.cpp'), LIBS=["pthread", "emon"])

# Emacs local variables
# Local variables:
# mode: python
# End:
