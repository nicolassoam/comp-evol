@echo off
make -C .\build 
setlocal EnableDelayedExpansion

set num_runs=20

for /l %%i in (1,1,%num_runs%) do (
    start /wait .\build\main !RANDOM!
)

