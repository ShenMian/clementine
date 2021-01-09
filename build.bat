@echo off
REM Copyright 2020 SMS
REM License(Apache-2.0)

cd %~dp0
if not exist build mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
ctest
