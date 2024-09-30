# Blank Cadmium Project

## Introduction
This is a blank project that you can use to start off your DEVS models. There is one Atomic and coupled model respectively.

## Dependencies
This project assumes that you have Cadmium installed in a location accessible by the environment variable $CADMIUM.

## Build
To build this project, run:
```sh
source build.sh
```
__NOTE__: Everytime you run build.sh, the contents of `build/` and `bin/` will be replaced.

## Execute
To run the project, run:
```sh
./bin/sample_project
```

## Modify
You can modify this project per your requirement. Change the project name defined in the topmost CMakeLists.txt file here:
```cmake
set(projectName "sample_project")
```
