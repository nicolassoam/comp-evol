@echo off
make -C .\build 
setlocal EnableDelayedExpansion

set num_runs=10

for /l %%i in (1,1,%num_runs%) do (
    start /wait .\build\main !RANDOM!
)

