@echo off

REM Path to testing program going throw 1-st argument of command string
SET CopyProgram="%~1"

REM Protection from start without argument
if %CopyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%CopyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy non empty file
%CopyProgram% NonEmpty.txt "%TEMP%\output.txt" || goto err
fc NonEmpty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed


REM Copy missing file should fail
%CopyProgram% Missing.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM If output file is not specified, program should fail
%CopyProgram% Missing.txt && goto err
echo Test 4 passed

REM If arguments is absent, program should fail
%CopyProgram% && goto err
echo Test 5 passed

REM Tests was saccessfully
echo All tests passed successfuly
exit /B 0

REM Tests finished with error
:err
echo Test failed
exit /B 1