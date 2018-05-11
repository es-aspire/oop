set PROGRAM="%~1"
                          
REM проверка работы программы при неверном количестве входных аргументов
%PROGRAM% 
if ERRORLEVEL EQU 0 goto err
echo test "invalid arguments count" succeeded 
 
REM проверка при пустом параметре <source notation>
%PROGRAM% "" 26 FF
if ERRORLEVEL EQU 0 goto err
echo test "empty <source notation>" succeeded 

REM переполнение при переводе <source notation>
%PROGRAM% 999999999999999999999 26 FF
if ERRORLEVEL EQU 0 goto err
echo test "overflow <source notation>" succeeded 

REM проверка при пустом параметре <destination notation>
%PROGRAM% 26 "" FF
if ERRORLEVEL EQU 0 goto err
echo test "empty <destination notation>" succeeded

REM переполнение при переводе <destination notation>
%PROGRAM% 2 999999999999999999999 0101100
if ERRORLEVEL EQU 0 goto err
echo test "overflow <destination notation>" succeeded 
                                
REM проверка при пустом параметре <value>
%PROGRAM% 18 26 ""
if ERRORLEVEL EQU 0 goto err
echo test "empty <value>" succeeded  

REM проверка при параметре <value>, содержащей недопустимые символы в <source notation>
%PROGRAM% 2 26 %#42 
if ERRORLEVEL EQU 0 goto err
echo test "invalid <value>" succeeded  
     
REM проверка перевода числа 010101 из 56-ой системы счисления в 26-ую
%PROGRAM% 56 26 010101 
if ERRORLEVEL EQU 0 goto err
echo test "010101 from 56th notation to 26th notation" succeeded                       

REM проверка перевода числа ZF из 2-ой системы счисления в 26-ую
%PROGRAM% 36 56 ZF 
if ERRORLEVEL EQU 0 goto err
echo test "ZF from 36th notation to 56th notation" succeeded                       

REM проверка перевода числа ZF из 36-ой системы счисления в 23-ую
%PROGRAM% 36 23 ZFZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ 
if ERRORLEVEL EQU 0 goto err
echo test "overflow" succeeded                       

REM проверка перевода числа 010101 из 2-ой системы счисления в 26-ую
%PROGRAM% 2 26 010101 
if ERRORLEVEL EQU 1 goto err
echo test "010101 from 2th notation to 26th notation" succeeded                       

REM проверка перевода числа 15436 из 2-ой системы счисления в 26-ую
%PROGRAM% 27 2 15436 
if ERRORLEVEL EQU 1 goto err
echo test "15436 from 27th notation to 2th notation" succeeded                       

REM проверка перевода числа -174G из 27-ой системы счисления в 3-ую
%PROGRAM% 27 3 -174G 
if ERRORLEVEL EQU 1 goto err
echo test "-174G from 27th notation to 3th notation" succeeded                       

ECHO Program testing succeeded :-)
EXIT 0

:err
ECHO Program testing failed :-(
EXIT 1