from SCons.Script import AlwaysBuild, Default, DefaultEnvironment
"""
This is a VERY hackish way to make platformio run local (on the PC/Mac) unit tests
 - Only one test executable is supported ('test_color_exec' compiled from 'color/test_color.cpp')
 - No arduino (or other board specific) libraries can be included in the executable

Setup:
1) Create a dedicated platformio.ci.ini:

     [env:unit_test]
     platform = native
     extra_script = src/test_runner.py

2) Exclude all arduino specific files and all non-test main files, use test directory as src

     platformio ci --lib="." \
       --project-conf platformio.ci.ini \
       --exclude=lib/aquarium_lights/src/debug/\* \
       --exclude=lib/aquarium_lights/src/main.cpp  \
       --lib="test_lib/unity" \
       test

Problems:
  - Adding multiple test files does NOT work, bc the compilation of 'program' lumps together every testfile in one executable and fails with duplicate symbols
"""

import os

env = DefaultEnvironment()

#env.Dump()


def builder_unit_test(target, source, env):
    app = str(source[0].abspath)
    return os.spawnl(os.P_WAIT, app, app)

# Create a builder for tests
bld = Builder(action = builder_unit_test)
env.Append(BUILDERS = {'Test' :  bld})

# Test
test_lib1 = env.Program( 'test_color_exec','color/test_color.cpp')


tests = [env.Test("test.passed.1", test_lib1)]

Default(tests)
