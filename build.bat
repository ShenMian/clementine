
@echo off
cd %~dp0
if not exist build mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
ctest
