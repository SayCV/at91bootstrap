@echo off
echo Copyright 2011 SayCV Inc. All rights reserved.
echo Use of this source code is governed by a BSD-style
echo license that can be found in the LICENSE file.
echo.
echo 2011 @ SayCV.Xiao
echo.

cd /d %~dp0
rem set PATH=D:\MinGW\msys\1.0\bin;D:\MinGW\msys\1.0\local\bin;D:\MingW\bin;D:\cygwin\home\Go\bin;D:\cygwin\home\Mercurial;D:\cygwin\bin;%PATH%

rem set PATH=D:\cygwin\home\gtk\bin;%PATH%
set PATH=D:\cygwin\opt\rtems-4.11-tools\bin;%PATH%
set PATH=D:\cygwin\opt\Sourcery_CodeBench_Lite_for_ARM_EABI\bin;%PATH%
set PATH=D:\cygwin\home\rtems\bin;%PATH%
set PATH=D:\cygwin\bin;%PATH%
set HOME=%cd%

set CROSS_COMPILE=arm-rtems-
rem set CROSS_COMPILE=arm-none-eabi-
rem set CROSS_COMPILE=arm-rtemseabi4.11-
set ERASE_FCT=del /F
make clean

echo Compile Bootstrap for sam9x25
if not exist .config (
rem cd board/at91sam9x5ek
bash --login -i -c "make at91sam9x5nf_defconfig"
rem make at91sam9x5norf_defconfig
rem cd ../..
)
bash --login -i -c "make"
set SRC_PATH=%cd%
echo Copy Files To Dest...
set DEST_PATH="C:/Docume~1/xiaoyc00181/×ÀÃæ/2012-5-15/AT91SAM9x5/Demos"
cd /d %DEST_PATH%
copy "%SRC_PATH%\binaries\at91sam9x5ek-norflashboot-3.1.bin"
copy "%SRC_PATH%\binaries\at91sam9x5ek-nandflashboot-3.1.bin"

pause