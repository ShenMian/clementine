**zh** | [en]

<div align="center">
<img src="docs/picture/banner.png">

[![License](https://img.shields.io/github/license/ShenMian/Clementine)](https://github.com/ShenMian/Clementine/blob/master/LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/shenmian/clementine/badge)](https://www.codefactor.io/repository/github/shenmian/clementine)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c09e10a19377466b99cc74d4f43ac214)](https://app.codacy.com/gh/ShenMian/Clementine?utm_source=github.com&utm_medium=referral&utm_content=ShenMian/Clementine&utm_campaign=Badge_Grade_Settings)
[![LGTM](https://img.shields.io/lgtm/grade/cpp/g/ShenMian/Clementine.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ShenMian/Clementine/context:cpp)
[![CI](https://github.com/ShenMian/Clementine/actions/workflows/ci.yml/badge.svg)](https://github.com/ShenMian/Clementine/actions/workflows/ci.yml)

</div>

这是一个用于制作2D命令行游戏的框架.   

- [文档](#文档)
- [特点](#特点)
- [截图](#截图)
- [编译](#编译)
- [联系](#联系)

文档
----
👉 **[Github Wiki]** (中文)  
👉 **[API参考]** (中文)  

特点 🎄
----
- 多平台: Linux, macOS, Windows.
- 轻量.
- 拥有内置CPU抽样性能分析器.
- 使用实体-组件系统(ECS).

截图 ✨
----
<img src="docs/picture/profiler.png" width="80%" height="80%">
<img src="docs/picture/picture_0.png" width="80%" height="80%">

编译 ⛓
----
[设置Git]并[fork我们的仓库]. 如果您更倾向于不使用Git, 点击右上角的'Download ZIP'来下载zip格式的源代码.

### Premake
进入文件夹 'scripts' 并执行 'generate_[action]_project.sh'/'generate_[action]_project.bat'. 这将生成对应特定软件的项目文件.

#### Action 选项
- `vs2019` Visual Studio 2019
- `xcode4` Xcode4
- `gmake2` GNU Make 2

### CMake
进入文件夹 'scripts' 并执行 'build.sh'/'build.bat'. 这将下载子模块并使用 CMake 构建项目.

### CMake 选项 (默认 ON)
- `BUILD_EXAMPLES` 构建示例
- `BUILD_TESTS`    构建单元测试

联系 💬
----
- **[Github Discussions]**
- **[Telegram]**

[en]:                 README.md
[API参考]:            https://shenmian.github.io/Clementine
[设置Git]:            https://help.github.com/articles/set-up-git
[fork我们的仓库]:      https://help.github.com/articles/fork-a-repo
[Github Wiki]:         https://github.com/ShenMian/Clementine/wiki
[Github Discussions]: https://github.com/ShenMian/Clementine/discussions
[Telegram]:           https://t.me/shenmian
