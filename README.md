**en** | [cn]

<div align="center">

[![License](https://img.shields.io/github/license/ShenMian/Clementine)](https://github.com/ShenMian/Clementine/blob/master/LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/shenmian/clementine/badge)](https://www.codefactor.io/repository/github/shenmian/clementine)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c09e10a19377466b99cc74d4f43ac214)](https://app.codacy.com/gh/ShenMian/Clementine?utm_source=github.com&utm_medium=referral&utm_content=ShenMian/Clementine&utm_campaign=Badge_Grade_Settings)
[![LGTM](https://img.shields.io/lgtm/grade/cpp/g/ShenMian/Clementine.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ShenMian/Clementine/context:cpp)
[![CI](https://github.com/ShenMian/Clementine/actions/workflows/ci.yml/badge.svg)](https://github.com/ShenMian/Clementine/actions/workflows/ci.yml)

</div>

This is a framework for building 2D console games.  

- [Documentation](#documentation)
- [Features](#features)
- [Screenshots](#screenshots)
- [Compiling](#compiling)
- [Contact](#contact)

Documentation
-------------
👉 **[Github Wiki]** (Chinese)  
👉 **[API Reference]** (Chinese)  

Features
--------
- Multi-platform: Linux, macOS, Windows.
- Lightweight.
- Has a built-in CPU sampling profiler.
- Using entity-component-system(ECS).

Screenshots
-----------
<img src="docs/picture/profiler.png" width="80%" height="80%">
<img src="docs/picture/clem_0.png" width="80%" height="80%">

Compiling
---------
[Set up Git] and [fork our repository].
If you'd prefer not to use Git, use the 'Download ZIP' button on the right to get the source as a zip file.

### Premake
Enter folder 'scripts' and run 'generate_[action]_project.sh'/'generate_[action]_project.bat'. This will generate the project files corresponding to specific software.

#### Action options
- `vs2019` Visual Studio 2019
- `xcode4` Xcode4
- `gmake2` GNU Make 2

### CMake
Enter folder 'scripts' and run 'build.sh'/'build.bat'. This will download submodules and use CMake to build project.

#### CMake Options (default ON)
- `BUILD_EXAMPLES` Build the examples
- `BUILD_TESTS`    Build the unit tests

Contact
-------
- **[Github Discussions]**
- **[Telegram]**

[cn]:                  README-cn.md
[API Reference]:       https://shenmian.github.io/Clementine
[Set up Git]:          https://help.github.com/articles/set-up-git
[fork our repository]: https://help.github.com/articles/fork-a-repo
[Github Wiki]:         https://github.com/ShenMian/Clementine/wiki
[Github Discussions]:  https://github.com/ShenMian/Clementine/discussions
[Telegram]:            https://t.me/shenmian
