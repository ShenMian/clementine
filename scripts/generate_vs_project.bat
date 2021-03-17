@echo off
REM Copyright 2021 SMS
REM License(Apache-2.0)

REM 切换到主目录
pushd %~dp0\..
REM 生成VS解决方案
thirdparty\premake\bin\premake5.exe vs2019
REM 打开解决方案
start clementine.sln
popd
