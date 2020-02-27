# Generate keywords from src folder into ../keywords.txt
~/.local/bin/arduino-keywords src --output ..

# Remove operator= from keywords.txt
sed -i '/operator=/d' keywords.txt

# Make build dir
rm -r build #for local development
mkdir build
cd build

# Make the project
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make

# Create baseline
lcov -c -i -d src/CMakeFiles/ -o base.info

# Testing
ctest --output-on-failure .

# Merge baseline with testing
lcov -c -d tests/CMakeFiles/ -o test.info
lcov -l test.info #debug
lcov -a base.info -a test.info -o total.info #merge base and test info
lcov -r total.info '/usr/*' '*/catchlib/*' '*/tests/*' -o total.info #remove trash