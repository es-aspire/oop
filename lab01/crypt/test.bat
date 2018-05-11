set PROGRAM="%~1"    

REM проверка работы программы при неверном количестве входных аргументов
%PROGRAM% 
if ERRORLEVEL EQU 0 goto err
echo test "invalid arguments count" succeeded       

REM проверка работы программы при пустом имени входного файла
%PROGRAM% ""
if ERRORLEVEL EQU 0 goto err
echo test "empty input file name" succeeded 

REM проверка работы программы при невалидном <action>
%PROGRAM% 213 input.txt "%TEMP%\output.txt" 24
if ERRORLEVEL EQU 0 goto err
echo test "invalid <action>" succeeded 
                                            
%PROGRAM% crypt empty.txt "%TEMP%\empty.txt" 17
if ERRORLEVEL EQU 0 goto err 
echo test "non existing input file"

%PROGRAM% crypt non-existing-file-name.txt "%TEMP%\non-existing-file-name.txt" 17
if ERRORLEVEL EQU 0 goto err 
echo test "non existing input file"

REM проверка работы программы при невалидном входном файле
%PROGRAM% crypt %PROGRAM% "%TEMP%\output.txt" 24
if ERRORLEVEL EQU 0 goto err
echo test "invalid input file name" succeeded 

REM проверка работы программы при пустом имени выходного файла
%PROGRAM% crypt "" "%TEMP%\output.txt" 24
if ERRORLEVEL EQU 0 goto err
echo test "empty output file name" succeeded 

REM проверка работы программы при невалидном выходном файле
%PROGRAM% crypt input.txt %PROGRAM% 255  
if ERRORLEVEL EQU 0 goto err
echo test "invalid output file name" succeeded 
                                              
REM проверка работы программы при <key>, €вл€ющимс€ числом не из дес€тичной системы счислени€
%PROGRAM% crypt input.txt "%TEMP%\output.txt" FF  
if ERRORLEVEL EQU 0 goto err
echo test "invalid notation" succeeded 

REM проверка работы программы, когда <key> не входит в допустимый диапазон 
%PROGRAM% crypt input.txt "%TEMP%\output.txt 999  
if ERRORLEVEL EQU 0 goto err
echo test "invalid range1" succeeded 

REM проверка работы программы, когда <key> не входит в допустимый диапазон 
%PROGRAM% crypt input.txt "%TEMP%\output.txt" -1
if ERRORLEVEL EQU 0 goto err
echo test "invalid range2" succeeded  
                                   
REM проверка шифровани€ и дешифровани€
%PROGRAM% crypt input.txt "%TEMP%\input.crypt.txt" 56
if ERRORLEVEL EQU 1 goto err  
%PROGRAM% decrypt "%TEMP%\input.crypt.txt" "%TEMP%\input.decrypt.txt" 56
if ERRORLEVEL EQU 1 goto err
fc /B "%TEMP%\input.decrypt.txt" input.txt
if ERRORLEVEL 1 goto err
echo test "crypt and decrypt" succeeded

REM проверка шифровани€ и дешифровани€ exe файла
%PROGRAM% crypt replace.exe "%TEMP%\replace.crypt.exe" 56
if ERRORLEVEL EQU 1 goto err  
%PROGRAM% decrypt "%TEMP%\replace.crypt.exe" "%TEMP%\replace.decrypt.exe" 56
if ERRORLEVEL EQU 1 goto err
fc.exe /B "%TEMP%\replace.decrypt.exe" replace.exe
if ERRORLEVEL 1 goto err
echo test "crypt and decrypt" succeeded

REM проверка шифровани€ и дешифровани€ самого себ€
%PROGRAM% crypt %PROGRAM% "%TEMP%\crypt.crypt.exe" 56
if ERRORLEVEL EQU 1 goto err  
%PROGRAM% decrypt "%TEMP%\crypt.crypt.exe" "%TEMP%\crypt.decrypt.exe" 56
if ERRORLEVEL EQU 1 goto err
fc.exe /B "%TEMP%\crypt.decrypt.exe" %PROGRAM%
if ERRORLEVEL 1 goto err
echo test "crypt and decrypt" succeeded


ECHO Program testing succeeded :-)
EXIT 0

:err
ECHO Program testing failed :-(
EXIT 1