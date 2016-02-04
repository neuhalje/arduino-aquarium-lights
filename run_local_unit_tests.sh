#!/bin/sh

platformio ci --lib="." --project-conf platformio.ci.ini --exclude=lib/aquarium_lights/src/debug/\* --exclude=lib/aquarium_lights/src/main.cpp   --keep-build-dir   --lib="test_lib/unity"  test
