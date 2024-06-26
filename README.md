## Compiling
1) Set the LLVM installation directory  ```$ LLVM_INSTALL_DIR=llvm_project_dir```
2) Set Up the build: ```$ cmake -DLLVM_INSTALL_DIR=$LLVM_INSTALL_DIR -G "Build System" -B build/```
3) Compile it: ```$ cd build``` and ```$ cmake --build .```

## Running
1) Compile your program to llvm IR: ```$ clang++ -emit-llvm -S myprogram.cpp -o myprogram.ll```
2) Run the pass: ```llvm-opt -load-pass-plugin ../build/lib/libCGAnalyzer.so -passes "fExtractor" -disable-output myprogram.ll```
