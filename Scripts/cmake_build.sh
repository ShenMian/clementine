#!/bin/bash
# Copyright 2021 ShenMian
# License(Apache-2.0)

# 切换到主目录
cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd ..

# 签出第三方库
git submodule update --init

# 創建 build 目錄
mkdir build
cd build

# 生成 CMake 緩存
cmake ..

# 構建
cmake --build .
