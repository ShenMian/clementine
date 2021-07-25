#!/bin/bash
# Copyright 2021 SMS
# License(Apache-2.0)

# 切换到主目录
cd "$( cd "$( dirname "$0"  )" && pwd  )"
cd ..

./Thirdparty/premake/bin/premake5 gmake2
