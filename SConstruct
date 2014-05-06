debugEnv = Environment()
debugEnv.Append(CXXFLAGS = ['-g'])

debugEnv.Program('program', Glob('src/*.cpp') + Glob('src/**/*.cpp'))
