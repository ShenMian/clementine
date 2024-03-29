@echo off
REM Copyright 2023 ShenMian
REM License(Apache-2.0)

conan --version >nul 2>&1 || (
    echo === Need conan.
    exit /b 1
)

cd %~dp0\.. || exit /b 1

set "build_type=%~1"
if "%build_type%"=="Debug" (set "msvc_args=MTd") else (set "msvc_args=MT")

set "build_path=target/%build_type%"

echo === Installing dependencies...
REM vcpkg
REM if exist "./deps/vcpkg/vcpkg" call deps/vcpkg/bootstrap-vcpkg.bat
REM deps/vcpkg/vcpkg install
vcpkg install

REM conan
set "CONAN_SYSREQUIRES_MODE=enabled"
conan install . -pr:b=default --build=missing -of "%build_path%" -s build_type=%build_type% || (
    echo === Failed to install.
    exit /b 1
)
conan install ./deps/graphics -pr:b=default --build=missing -of "%build_path%" -s build_type=%build_type% || (
    echo === Failed to install.
    exit /b 1
)
