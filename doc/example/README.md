# How to use Badhron in a CMake project

## Build instructions
```sh
mkdir build
cd build
cmake .. \
    -DAnyDSL_runtime_DIR=/<path to anydsl>/runtime/build/share/anydsl/cmake \
    -DCMAKE_PREFIX_PATH=/path/to/badhron/install/prefix
```
These instructions assume that [AnyDSL](https://github.com/anydsl/anydsl) was compiled 
through its provided `setup.sh` script (as recommended by the project's README file). 
Further, the `CMAKE_PREFIX_PATH` must usually only be provided if Badhron was installed 
into a non-standard location (e.g., using CMake's `--prefix` option).
