set PROGRAM="%~1"     
                    
REM запуск программы без параметров
%PROGRAM% 
IF ERRORLEVEL EQU 0 GOTO err
echo test "without parameter" succeeded
                   
REM проверяем нахождение пути в лабиринте из несуществующего файла
%PROGRAM% non-existing-file.txt 
IF ERRORLEVEL EQU 0 GOTO err 
echo test "non existing input file" succeeded

REM проверяем нахождение пути в лабиринте из пустого файла
%PROGRAM% empty.txt "%TEMP%\output.txt"  
IF ERRORLEVEL EQU 0 GOTO err
echo test "empty input file" succeeded
 
REM проверяем чтение не валидного входного файла
%PROGRAM% invalid-map.txt "%TEMP%\invalid-map"
if ERRORLEVEL EQU 0 GOTO err
echo test "invalid input file" succeeded
                          
REM проверяем ситуацию, когда неверное число стартовых позиций  
%PROGRAM% invalid-start-pos-count.txt "%TEMP%\invalid-start-pos-count.txt"
IF ERRORLEVEL EQU 0 GOTO err
echo test "invalid start position count" succeeded               

REM проверяем ситуацию, когда неверное число конечных позиций  
%PROGRAM% invalid-end-pos-count.txt "%TEMP%\invalid-end-pos-count.txt"
IF ERRORLEVEL EQU 0 GOTO err
echo test "invalid end position count" succeeded 
                   
REM matrix-more-100-without-end-position
%PROGRAM% matrix-more-100-without-end-position.txt "%TEMP%\matrix-more-100-without-end-position.txt"
IF ERRORLEVEL EQU 0 GOTO err 
echo test "matrix-more-100-without-end-position" succeeded
                      
REM проверяем ситуацию, когда отстутствует путь
%PROGRAM% no-path.txt "%TEMP%\no-path.txt"
IF ERRORLEVEL EQU 1 GOTO err
fc.exe "%TEMP%\no-path.txt" check-no-path.txt
IF ERROROLEVEL EQU 1 GOTO err  
echo test "no path" succeeded                 
                   
REM проверяем ситуацию, когда верное число стартовых и конечных позиций  
%PROGRAM% matrix1.txt "%TEMP%\matrix1.txt"
IF ERRORLEVEL EQU 1 GOTO err
fc.exe "%TEMP%\matrix1.txt" check-matrix1.txt
IF ERROROLEVEL EQU 1 GOTO err  
echo test "matrix1" succeeded
  
REM проверяем ситуацию, когда верное число стартовых и конечных позиций  
%PROGRAM% matrix2.txt "%TEMP%\matrix2.txt"
IF ERRORLEVEL EQU 1 GOTO err
fc.exe "%TEMP%\matrix2.txt" check-matrix2.txt
IF ERROROLEVEL EQU 1 GOTO err
echo test "matrix2" succeeded
           
REM matrix100x100 
%PROGRAM% matrix100x100.txt "%TEMP%\matrix100x100.txt"
IF ERRORLEVEL EQU 1 GOTO err
fc.exe "%TEMP%\matrix100x100.txt" check-matrix100x100.txt
IF ERROROLEVEL EQU 1 GOTO err
echo test "matrix100x100" succeeded

REM matrix-more-100-with-path 
%PROGRAM% matrix-more-100-with-path.txt "%TEMP%\matrix-more-100-with-path.txt"
IF ERRORLEVEL EQU 1 GOTO err
fc.exe "%TEMP%\matrix-more-100-with-path.txt" check-matrix-more-100-with-path.txt
IF ERROROLEVEL EQU 1 GOTO err
echo test "matrix-more-100-with-path" succeeded


REM ожидаем ненулевой код ошибки при невозможности записи в выходной файл
%PROGRAM% input.txt %PROGRAM% 
if ERRORLEVEL EQU 0 goto err
echo test "data flushed to disk" succeeded

      
ECHO Program testing succeeded :-)
EXIT 0

:err
ECHO Program testing failed :-(
EXIT 1