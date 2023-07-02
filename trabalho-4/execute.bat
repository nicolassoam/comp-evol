@echo off
make -C .\build 


set num_runs=20

for /l %%i in (1,1,%num_runs%) do (
    start /wait .\build\main %%i
)

