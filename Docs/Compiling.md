# Compiling

使用 CMake
----------
**警告: 暂不支持**  
执行 `Scripts` 下 `cmake_build` 开头的脚本 将使用 CMake 在 `build` 目录下进行构建.

使用 Premake5
-------------
执行 `Scripts` 下 `gen_` 开头的脚本将使用 [premake5](https://github.com/premake/premake-core) 快速於生成常見 IDE 的項目文件.
目前支持的 IDE 有:
- Microsoft Visual Studio 2005-2019
- GNU Make, including Cygwin and MinGW
- Xcode
- Codelite
