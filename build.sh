#make build dir
rm -r build #for local development
mkdir build
cd build

#make the project
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make

#create baseline
lcov -c -i -d src/CMakeFiles/ -o base.info

#testing
ctest --output-on-failure .

#merge baseline with testing
lcov -c -d tests/CMakeFiles/ -o test.info
lcov -l test.info #debug
lcov -a base.info -a test.info -o total.info #merge base and test info
lcov -r total.info '/usr/*' 'catchlib/*' 'tests/*' -o total.info #remove trash