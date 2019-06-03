mkdir build
cd build
cmake ..
make
make test
ctest --output-on-failure .