#!/bin/bash
# Copyright 2022 ShenMian
# License(Apache-2.0)

build_dir=target

build_type=$1
compiler=$2
# compiler_version=$3
shift
shift
shift

if [ -z "${build_type}" ]; then
    build_type=Debug
fi
if [ -z "${compiler}" ]; then
    compiler=clang
fi
if [ -z "${compiler_version}" ]; then
    compiler_version=$(clang --version | head -n1 | cut -d' ' -f3 | cut -d'.' -f1)
fi

if [ "${compiler}" = "clang" ]; then
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
else
    echo "=== Unsupported compiler."
    exit 1
fi

echo "=== Installing dependencies..."
export CONAN_SYSREQUIRES_MODE=enabled
conan install . -pr:b=default --build=missing -if $build_dir -of $build_dir -s build_type=$build_type -s compiler=${compiler} -s compiler.version=${compiler_version} -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True || {
    echo "=== Failed to install."
    exit 1
}
