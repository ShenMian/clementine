#!/bin/bash
# Copyright 2020 SMS
# License(Apache-2.0)

# 切换到脚本所在目录
cd "$( cd "$( dirname "$0"  )" && pwd  )"

# 建立 build 目录, 用于构建
if [ ! -d "./build" ]; then
	mkdir build
fi
cd build

# 下载子模块, 包含第三方库
git submodule update --init --recursive

# 构建
cmake ..
cmake --build .

# 运行单元测试
ctest

