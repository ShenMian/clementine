#!/bin/bash
# Copyright 2021 ShenMian
# License(Apache-2.0)

# 切换到 ThirdParty 目录
cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd ../ThirdParty

# 獲取管理員權限
if ! sudo echo
then
    echo "Can not get sudo permission."
    exit 1
fi

# 签出第三方库
echo Checkout third-party libraries...
if ! git submodule update --init >/dev/null
then
    echo Failed to checkout third-party libraries.
    exit 1
fi

echo Installing dependencies...

deps=("assimp" "glfw" "meshoptimizer")
for (( i = 0 ; i < ${#deps[@]} ; i++ ))
do
    cd "${deps[$i]}" || exit

    echo "|-Installing '${deps[$i]}'..."

    # 生成 CMake 緩存
    echo " |-Gerenating CMake cache..."
    if ! cmake -B build >/dev/null 2>&1
    then
        echo " |-Failed to generate CMake cache."
        exit 1
    fi

    # 构建
    echo " |-Building..."
    if ! cmake --build build --config Release >/dev/null
    then
        echo " |-Failed to build."
        cmake --build build --config Release
        exit 1
    fi

    # 安装
    echo  " |-Installing..."
    if ! sudo cmake --install build >/dev/null
    then
        echo " |-Failed to install."
        exit 1
    fi

    echo " |-Done."

    cd ..
done
