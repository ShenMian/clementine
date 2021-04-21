@echo off
REM Copyright 2021 SMS
REM License(Apache-2.0)

REM 切换到主目录
pushd %~dp0\..
git submodule update --init --recursive
REM 创建build目录
if not exist build mkdir build
pushd build
REM CMake构建
cmake ..
cmake --build .
popd
popd
