@echo off
REM Copyright 2022 ShenMian
REM License(Apache-2.0)

set "BUILD_DIR=build"

cmake --version >nul 2>&1 || (
    echo === Need cmake.
    exit /b 1
)

if "%~1"=="" (set "BUILD_TYPE=Debug") else (set "BUILD_TYPE=%~1")
if "%BUILD_TYPE%"=="Debug" (set "VS_ARGS=MTd") else (set "VS_ARGS=MT")

cd %~dp0\.. || exit /b 1

mkdir build 2>nul

echo === Installing dependencies...
set "CONAN_SYSREQUIRES_MODE=enabled"
conan install ./deps/Graphics --build=missing -if %BUILD_DIR% -of %BUILD_DIR% -s build_type=%BUILD_TYPE% -s compiler.runtime=%VS_ARGS% >nul || (
    echo === Failed to install.
    exit /b 1
)
conan install . --build=missing -if %BUILD_DIR% -of %BUILD_DIR% -s build_type=%BUILD_TYPE% -s compiler.runtime=%VS_ARGS% >nul || (
    echo === Failed to install.
    exit /b 1
)

echo === Generating CMake cache...
cmake -Wno-dev -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -B %BUILD_DIR% >nul || (
    echo === Failed to generate CMake cache.
    exit /b 1
)

echo === Generating 'compile_commands.json'...
xcopy %BUILD_DIR%/compile_commands.json . 2>nul || echo No 'compile_commands.json' was generated.

echo === Building...
cmake --build %BUILD_DIR% --config "%BUILD_TYPE%" -j16 || (
    echo === Failed to build.
    exit /b 1
)

echo === Done.
