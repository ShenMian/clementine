@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

REM 切换到主目录
pushd %~dp0\..

REM 生成 Makefile
Source\ThirdParty\premake\bin\premake5.exe gmake2

popd