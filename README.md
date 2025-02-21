# Encoded Multiplexer
|  Linux | Windows| ESP32 | MSP432 |
|:--|:--|:--|:--|
|:heavy_check_mark:|:question:|:question:|:question:|
## Introduction
This is a DEVS model of a multiplexer (encoded because the input port select is encoded in the output), and a tester model to test the multiplexer for different number of ports.

## Dependencies
This project assumes that you have Cadmium installed in a location accessible by the environment variable $CADMIUM.
_This dependency would be met by default if you are using the DEVSsim servers. To check, try `echo $CADMIUM` in the terminal_

## Build
To build this project, run:
```sh
source build_sim.sh
```
__NOTE__: Everytime you run build_sim.sh, the contents of `build/` and `bin/` will be replaced.

To build this project for real time, run:
```sh
source build_rt.sh
```

## Execute
To run the project, run:
```sh
./bin/mux_test
```