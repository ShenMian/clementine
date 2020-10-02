
@echo off
cd %~dp0
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
ctest
