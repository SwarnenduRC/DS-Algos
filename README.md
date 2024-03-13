# DS-Algos

Solutions to various algorithmic problems based on various data structures

## Description

It is a repo of various algorithmic problems related to different data structures in modern C++-17.

## Build

To build the application simply make which will build two
binaries under the bin folder for Debug & Release. To clean 
it run `make clean`. To build only debug/release run `make debug` 
or `make release`.

## Tests

The console application itself is a Google test application that is used to test
the various data structure classes and their methods. So you need to have a Google
test framework installed and active or available on your build machine to successfully
run this application. If you don't have one you can run the `GoogleTest.sh` script to
download and install the GoogleTest framework on your Mac machine (the script is made for
MacOS Ventura on an M2 machine but can be easily modified for any other OS and configuration)

## Memory Leaks

The console application has been tested for memory leaks using the `leaks` tool on MacOS Ventura
and none were found. You can run it by using `leaks --atExit --list -- ./bin/DS-AlgosD --gtest_shuffle --gtest_repeat=3`
