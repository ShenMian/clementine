@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

REM 检测是否有管理员权限
net.exe session 1>NUL 2>NUL || (
    echo Please run this script with administrator privilege.
    exit /b 1
)

pushd %~dp0\..\Source\ThirdParty

REM 签出第三方库
echo Checkout third-party libraries...
git submodule update --init >NUL || (
    echo Failed to checkout third-party libraries.
    exit /b 1
)

echo Installing dependencies...

for %%i in ("") do (
    echo ^|-Installing '%%~i'...

    pushd %%i

    REM 生成 CMake 緩存
    echo  ^|-Gerenating CMake cache...
    cmake -B build >NUL || (
        echo  ^|-Failed to generate CMake cache.
        exit /b 1
    )

    REM 构建
    echo  ^|-Building...
    cmake --build build --config Release >NUL || (
        echo  ^|-Failed to build.
        exit /b 1
    )

    REM 安装
    echo  ^|-Installing...
    cmake --install build >NUL || (
        echo  ^|-Failed to install.
        exit /b 1
    )

    echo  ^|-Done.

    popd
)

popd
