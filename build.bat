@echo off
REM Copyright 2020 SMS
REM License(Apache-2.0)

REM 切换到脚本所在目录
cd %~dp0

REM 建立 build 目录, 用于构建
if not exist build mkdir build
cd build

REM 下载子模块, 包含第三方库
git submodule update --init --recursive

REM 构建
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .

REM 运行单元测试
ctest
