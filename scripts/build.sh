#!/bin/bash
# Copyright 2022 ShenMian
# License(Apache-2.0)

build_dir=build

build_type=$1
compiler=$2 # 编译器只能是 clang/gcc
compiler_version=$3
shift
shift
shift

if ! hash "cmake" &>/dev/null; then
    echo "=== Need cmake."
    exit 1
fi

if [ -z "$build_type" ]; then
  build_type="Debug"
fi

if [ -n "$compiler" ] && [ -n "$compiler_version" ]; then
  conan_args="-s build_type=$build_type -s compiler=$compiler -s compiler.version=$compiler_version"
  cmake_args="-DCMAKE_BUILD_TYPE=$build_type -DCMAKE_C_COMPILER=$compiler -DCMAKE_CXX_COMPILER=$compiler++"
fi

cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd .. || exit

mkdir $build_dir 2>/dev/null

echo "=== Installing dependencies..."
export CONAN_SYSREQUIRES_MODE=enabled
conan install . --build=missing -if $build_dir -of $build_dir $conan_args -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True >/dev/null || {
  echo "=== Failed to install."
  exit 1
}

echo "=== Generating CMake cache..."
cmake -Wno-dev $cmake_args -B $build_dir >/dev/null || {
  echo "=== Failed to generate CMake cache."
  exit 1
}

echo "=== Generating 'compile_commands.json'..."
cp $build_dir/compile_commands.json . &>/dev/null || echo "No 'compile_commands.json' was generated."

echo "=== Building..."
cmake --build $build_dir --config "$build_type" -- -j$(nproc) >/dev/null || {
  echo "=== Failed to build."
  exit 1
}

echo "=== Done."
