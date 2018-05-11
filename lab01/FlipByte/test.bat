set PROGRAM="%~1"

REM пустой входной параметр 
%PROGRAM% ""
if NOT ERRORLEVEL 1 GOTO err
echo test "empty" succeeded

REM неверное число входных параметров
%PROGRAM% 8 26
if NOT ERRORLEVEL 1 GOTO err
echo test "invalid count input parameter" succeeded

REM нечисловой значение входного параметра
%PROGRAM% notNumber
if NOT ERRORLEVEL 1 GOTO err
echo test "not number"
         
REM min-valid-number-1    
%PROGRAM% -1
if NOT ERRORLEVEL 1 GOTO err
echo test "min-valid-number - 1" succeeded

REM test max-valid-number + 1
%PROGRAM% 256
if NOT ERRORLEVEL 1 GOTO err
echo test "max-valid-number + 1" succeeded

REM проверка программы при входном числе меньше минимально допустимого
%PROGRAM% -123
if NOT ERRORLEVEL 1 GOTO err
echo test "invalid range less"

REM проверка программы при входном числе меньше максимально допустимого
%PROGRAM% 3976
if NOT ERRORLEVEL 1 GOTO err
echo test "invalid range more" succeeded

REM 0 -> 0
%PROGRAM% 0 > "out-0.txt"
if ERRORLEVEL 1 GOTO err
fc "out-0.txt" check-0.txt
if ERRORLEVEL 1 GOTO err
echo test "0" succeeded

REM 255 -> 255
%PROGRAM% 255 > "out-255.txt"
if NOT ERRORLEVEL 0 GOTO err
fc "out-255.txt" check-255.txt
if NOT ERRORLEVEL 0 GOTO err
echo test "255" succeeded

REM 1 -> 128
%PROGRAM% 1 > "out-1.txt"
if NOT ERRORLEVEL 0 GOTO err
fc "out-1.txt" check-1.txt
if NOT ERRORLEVEL 0 GOTO err
echo test "0" succeeded

REM 6 -> 96
%PROGRAM% 6 > "out-6.txt"
if NOT ERRORLEVEL 0 GOTO err
fc "out-6.txt" check-6.txt
if NOT ERRORLEVEL 0 GOTO err
echo test "6" succeeded

REM 127 -> 254
%PROGRAM% 127 > "out-127.txt"
if NOT ERRORLEVEL 0 GOTO err
fc "out-127.txt" check-127.txt
if NOT ERRORLEVEL 0 GOTO err
echo test "127" succeeded

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
