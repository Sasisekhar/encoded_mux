# Blank Cadmium Project
Works on:
|  Linux | Windows| ESP32 | MSP432 |
|:--|:--|:--|
|:heavy_check_mark:|:heavy_check_mark:|:x:|:question:|
## Introduction
This is a blank project that you can use as a template to start off your DEVS models. This project consists of the .

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
