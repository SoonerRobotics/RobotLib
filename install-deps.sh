# Dependencies for building
sudo apt-get update
sudo apt-get install gcc lcov gcc-avr binutils-avr avr-libc -y

# Depdendencies for arduinokeywords
sudo apt-get install python-pip -y
python -m pip install --upgrade pip setuptools wheel
pip install arduinokeywords