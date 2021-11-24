@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" >NUL
) else (
    if exist "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Auxiliary\Build\vcvars64.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Auxiliary\Build\vcvars64.bat" >NUL
    ) else (
        echo Can't find vcvars64.bat
        exit /b 1
    )
)

REM 切换到主目录
pushd %~dp0\..

REM 安装依赖项
call Scripts/cmake_install_deps || exit /b 1

REM 生成 CMake 緩存
echo Generating CMake cache...
cmake -B build >NUL || (
    echo Failed to generate CMake cache.
    exit /b 1
)

REM 構建
echo Building...
cmake --build build >NUL || (
    echo Failed to build.
    cmake --build build
    exit /b 1
)

echo Done.

popd
