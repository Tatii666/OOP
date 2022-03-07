@echo off

REM Path to testing program going throw 1-st argument of command string
SET Multimatrix="%~1"

REM Protection from start without argument
if %Multimatrix%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Program start with empty matrix on input
%Multimatrix% testMatrix.txt matrix2.txt && goto err
echo Test 1 passed

REM checking on invalid arguments(string)


REM Tests was saccessfully
echo All tests passed successfuly
exit /B 0

REM Tests finished with error
:err
echo Test failed
exit /B 1