# To build 
mkdir build
cp ./shaders ./build -r
cd build 
cmake ..
make
./swar
