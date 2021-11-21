# Compiling

使用 Premake5
-------------
可以使用 [premake5](https://github.com/premake/premake-core) 來生成不同 IDE 的項目文件.
提供了幾個[腳本](./Scripts)用快速於生成常見 IDE 的項目文件.
目前支持的 IDE 有:
- Microsoft Visual Studio 2005-2019
- GNU Make, including Cygwin and MinGW
- Xcode
- Codelite

使用 CMake
----------
**警告: 即將支持**
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

