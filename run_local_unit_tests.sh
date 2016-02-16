#!/bin/sh

#  comment the following line to delete the build dir after tests
KEEP_BUILD_DIR="--keep-build-dir"

platformio ci --lib="." --project-conf platformio.ci.ini --exclude=lib/aquarium_lights/src/main.cpp   $KEEP_BUILD_DIR   --lib="test_lib/unity"  test
