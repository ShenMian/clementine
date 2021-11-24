#!/bin/bash
# Copyright 2021 ShenMian
# License(Apache-2.0)

# 切换到 ThirdParty 目录
cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd ../Source/ThirdParty

# 獲取管理員權限
sudo echo

# 签出第三方库
echo Checkout third-party libraries...
if ! git submodule update --init >/dev/null
then
    echo Failed to checkout third-party libraries.
    exit 1
fi

echo Installing dependencies...

deps=()
for (( i = 0 ; i < ${#deps[@]} ; i++ ))
do
    cd "${deps[$i]}" || exit

    # 生成 CMake 緩存
    echo "|-Gerenating CMake cache..."
    if ! cmake -B build >/dev/null
    then
        echo "|-Failed to generate CMake cache."
        exit 1
    fi

    # 构建
    echo "|-Building..."
    if ! cmake --build build --config Release >/dev/null
    then
        echo "|-Failed to build."
        exit 1
    fi

    # 安装
    echo  "|-Installing..."
    if ! sudo cmake --install build >/dev/null
    then
        echo "|-Failed to install."
        exit 1
    fi

    echo "|-Done."

    cd ..
done
