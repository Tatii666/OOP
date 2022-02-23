@echo off

REM Path to testing program going throw 1-st argument of command string
SET BinToDec="%~1"

REM Protection from start without argument
if %BinToDec%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Run with missing number should fail
%BinToDec% && goto err
echo Test 1 passed

REM If number is too long, program should fail
%BinToDec% 100100101101010110101010101011101011101011001010101 && goto err
echo Test 2 passed

REM If binary number exists not only 0 or 1, program should fail
%BinToDec% 1001245 && goto err
echo Test 3 passed

REM If binary number exists not only digits, program should fail
%BinToDec% 100ac && goto err
echo Test 4 passed

REM If coming element is not a digit, program should fail
%BinToDec% abcc && goto err
echo Test 5 passed

REM If coming digit is negative, program should fail
%BinToDec% -1011 && goto err
echo Test 6 passed

REM Tests was saccessfully
echo All tests passed successfuly
exit /B 0

REM Tests finished with error
:err
echo Test failed
exit /B 1