# How to use Badhron in a CMake project

## Build instructions
```sh
mkdir build
cd build
cmake .. \
    -DAnyDSL_runtime_DIR=/<path to anydsl>/build/share/anydsl/runtime \
    -DBadhron_DIR=/<path to badhron>/build/share/badhron/cmake
```
