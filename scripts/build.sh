#!/bin/bash
# Copyright 2022 ShenMian
# License(Apache-2.0)

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
if [ -z "$compiler" ]; then
    compiler=clang
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
fi

build_path=target/$build_type

if [ -n "$compiler" ] && [ -n "$compiler_version" ]; then
  cmake_args="-DCMAKE_BUILD_TYPE=$build_type -DCMAKE_C_COMPILER=$compiler -DCMAKE_CXX_COMPILER=$compiler++"
fi

cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd .. || exit

mkdir $build_path 2>/dev/null

./scripts/install_dependencies.sh $build_type $compiler $compiler_version || exit 1

echo "=== Generating CMake cache..."
cmake -B $build_path -Wno-dev -G Ninja $cmake_args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON >/dev/null || {
  echo "=== Failed to generate CMake cache."
  exit 1
}

echo "=== Generating 'compile_commands.json'..."
cp $build_path/compile_commands.json . &>/dev/null || echo "No 'compile_commands.json' was generated."

echo "=== Building..."
cmake --build $build_path --config "$build_type" -- -j$(nproc) || {
  echo "=== Failed to build."
  exit 1
}

echo "=== Done."
