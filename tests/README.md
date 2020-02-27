# Contributing to Testing

## Catch2
We use Catch2 for our unit testing framework. You can read more about it here https://github.com/catchorg/Catch2, but you probably can learn it through the examples in this directory alone.

## Adding new tests
If you would like to contribute new tests to new classes, simply create a new file called `test_NAME.cpp` where NAME is relevant to whatever class or function you are testing. Look at the other examples in this directory as a formatting guide. You should only need the following two imports
```cpp
#include <RobotLib.h>
#include <catch.hpp>
```
The build process will automatically find your new file during compilation. 

## Running tests locally

First, make sure you have necessary dependencies.

`./install-deps.sh`

You can run the unit tests by running `build.sh` while in base directory. This will create a new folder `build` with all the output. Any errors will be shown in stdout along with a brief summary of the coverage. If you would like to view a summary of the coverage in a webpage, you can run `genhtml build/total.info -o out/` and it will create a folder `out` that contains a static website.