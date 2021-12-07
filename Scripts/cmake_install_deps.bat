@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

REM 检测是否有管理员权限
net.exe session >nul 2>&1 || (
    echo Please run this script with administrator privilege.
    exit /b 1
)

pushd %~dp0\..\ThirdParty

REM 签出第三方库
echo Checkout third-party libraries...
git submodule update --init >nul 2>&1 || (
    echo Failed to checkout third-party libraries.
    exit /b 1
)

echo Installing dependencies...

for %%i in ("assimp" "glfw" "meshoptimizer") do (
    echo ^|-Installing '%%~i'...

    pushd %%i

    REM 生成 CMake 緩存
    echo  ^|-Gerenating CMake cache...
    cmake -B build >nul || (
        echo  ^|-Failed to generate CMake cache.
        exit /b 1
    )

    REM 构建
    echo  ^|-Building...
    cmake --build build --config Release >nul || (
        echo  ^|-Failed to build.
        cmake --build build --config Release
        exit /b 1
    )

    REM 安装
    echo  ^|-Installing...
    cmake --install build >nul || (
        echo  ^|-Failed to install.
        exit /b 1
    )

    echo  ^|-Done.

    popd
)

popd
