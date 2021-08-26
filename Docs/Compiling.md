# Compiling

**Warning**: The compiler must support the C++20 standard.  

[Set up Git] and [fork our repository].
If you'd prefer not to use Git, use the 'Download ZIP' button on the right to get the source as a zip file.

### Premake
Enter folder 'Scripts' and run 'generate_[action]_project.sh'/'generate_[action]_project.bat'. This will generate the project files corresponding to specific software.

#### Action options
- `vs2019` Visual Studio 2019.
- `xcode4` Xcode4.
- `gmake2` GNU Make 2.

### CMake
**Warning**: Unavailable for now.  
Enter folder 'Scripts' and run 'build.sh'/'build.bat'. This will download submodules and use CMake to build project.

#### CMake Options (default ON)
- `BUILD_EXAMPLES` Build the examples
- `BUILD_TESTS`    Build the unit tests