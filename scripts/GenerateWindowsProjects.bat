@echo off
pushd ..\
call vendor\bin\premake\premake5 vs2022
popd
PAUSE