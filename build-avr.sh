# Make build dir
rm -r build #for local development
mkdir build
cd build

# Make the project
cmake -DCMAKE_CXX_COMPILER='/usr/bin/avr-gcc' ..
make