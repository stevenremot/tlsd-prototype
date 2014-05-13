debugEnv = Environment()
debugEnv.Append(CXXFLAGS = ["-Wall", "-g"])

# Uncomment it to use Clanginstead of gcc
# Clang can be more verbose on some errors
# debugEnv.Replace(CC = "clang",
#                  CXX = "clang++")

# Uncommment if you need c++11 support for the standard library
# debugEnv.Append(CXXFLAGS = ["-std=c++11"])

debugEnv.Program('program', Glob('src/*.cpp') + Glob('src/**/*.cpp'), LIBS=["pthread"])
