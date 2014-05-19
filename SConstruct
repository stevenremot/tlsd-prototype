debugEnv = Environment()
debugEnv.Append(CXXFLAGS = ["-Wall", "-g"])

# Uncomment it to use Clang instead of gcc
# Clang can be more verbose on some errors
# debugEnv.Replace(CC = "clang",
#                  CXX = "clang++")

debugEnv.Program('program', Glob('src/*.cpp') + Glob('src/**/*.cpp'), LIBS=["pthreadGC2"])
