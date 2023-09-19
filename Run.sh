. SetEnvs.sh
cmake -S . -B ./build
cmake --build ./build
cp ./build/OpenGL .
./OpenGL
