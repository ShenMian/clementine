#!/bin/bash
# Copyright 2021 ShenMian
# License(Apache-2.0)

# 切换到主目录
cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd ..

# 生成 Makefile
./Source/ThirdParty/premake/bin/premake5 gmake2