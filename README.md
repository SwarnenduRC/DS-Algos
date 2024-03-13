# LeetCode

Solutions to various Leetcode's problems

## Description

It is a repo of various problems in Leetcode in modern C++-17.

## Build

To build the application simply make which will build two
binaries under the bin folder for Debug & Release. To clean 
it run `make clean`. To build only debug/release run `make debug` 
or `make release`. Also keep in mind that as all the data 
structures are templated ones and thus headers only so if you make 
any changes on any of the header file you need to run a clean build 
for the changes to take effect.

## Tests

The console application itself is a Google test application which is used to test
the various data structure classes and their's methods. So you need to have a Google
test framework installed and active or available on your build machine to successfully
run this application. If you don't have one you can run `GoogleTest.sh` script to
downlaod and install GoogleTest framework on your Mac machine (the script is made for
MacOS Ventura on M2 machine but can be easily modified for any other OS and configuration)

## Memory Leaks

The console application has been tested for memory leaks using `leaks` tool on MacOS Ventura
and none found. You can ru it by using `leaks --atExit --list -- ./bin/LeetCodeD --gtest_shuffle --gtest_repeat=3`