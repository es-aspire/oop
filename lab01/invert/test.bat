set PROGRAM="%~1"
                             
REM запуск программы без параметров
%PROGRAM%
IF ERRORLEVEL EQU 0 GOTO err
echo test "without parameter" succeeded
                                            
REM запуск программы с пустой строкой в качестве одного из параметров
%PROGRAM% "" 
IF ERRORLEVEL EQU 0 GOTO err
echo test "empty parameter" succeeded  

REM проверяем нахождение обратной матрицы из несуществующего файла
%PROGRAM% non-existing-file.txt
IF ERRORLEVEL EQU 0 GOTO err
echo test "non existing file" succeeded

REM проверяем нахождение обратной матрицы из пустого файла
%PROGRAM% empty.txt "%TEMP%\empty.txt" 
IF ERRORLEVEL EQU 0 GOTO err
echo test "empty input file" succeeded
 
REM проверяем чтение из невалидной матрицы                          
REM проверяем ситуацию, когда детерминант равен нулю    
%PROGRAM% zero-determinat.txt
IF ERRORLEVEL EQU 1 GOTO err  
echo test "zero determinant" succeeded

REM проверяем ситуацию, когда детерминант не равен нулю    
%PROGRAM% no-zero-determinat.txt > "%TEMP%\output.txt"
IF ERRORLEVEL EQU 1 GOTO err
fc.exe "%TEMP%\output.txt" check-no-zero-determinant.txt
IF ERROROLEVEL EQU 1 GOTO err
echo test "no zero determinant" succeeded
      
    
ECHO Program testing succeeded :-)
EXIT 0

:err
ECHO Program testing failed :-(
EXIT 1