@echo off
IF [%1]==[] (
    echo Value missing
    exit /b 1
)
gcc %~1.c -o /dist/%~1
echo Successfully compiled.
echo Executing %~1.exe...
/dist/%~1.exe