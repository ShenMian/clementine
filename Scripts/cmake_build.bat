@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

REM 切换到主目录
pushd %~dp0\..

REM 签出第三方库
git submodule update --init

REM 創建 build 目錄
mkdir build
cd build

REM 生成 CMake 緩存
cmake ..

REM 構建
cmake --build .

popd
