rm -rf build/
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 4
# cmake --build build --target install

# sh run.sh > make.log
sh run.sh