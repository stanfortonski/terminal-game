@echo off
rd cmake /s /q 
mkdir cmake
cd cmake
cmake -G "MinGW Makefiles" ..
%mingw32-make%
pause