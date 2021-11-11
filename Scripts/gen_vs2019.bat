@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

REM 切换到主目录
pushd %~dp0\..
if not exist Graphics.sln set firstGenerate=true

REM 生成VS解决方案
Source\ThirdParty\premake\bin\premake5.exe vs2019
if errorlevel 1 pause

REM 打开解决方案
if "%firstGenerate%"=="true" start Graphics.sln

popd