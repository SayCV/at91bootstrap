@echo on
echo Copyright 2011 SayCV Inc. All rights reserved.
echo Use of this source code is governed by a BSD-style
echo license that can be found in the LICENSE file.
echo.
echo 2011 @ SayCV.Xiao
echo.

cd /d %~dp0
set PATH=D:\MinGW\msys\1.0\bin;D:\MinGW\msys\1.0\local\bin;D:\MingW\bin;%PATH%

set HOME=%cd%
set ORIGIN_HOME=%cd%
set PATH=%HOME%/../../repo_SayCV-RTEMS-SAM9X25/SayCVmxe/usr/bin;%PATH%
set PATH=%HOME%/../../repo_SayCV-RTEMS-SAM9X25/SayCVmxe/usr/arm-rtemseabi4.11/bin;%PATH%
set PATH=D:\cygwin\opt\Sourcery_CodeBench_Lite_for_ARM_EABI\bin;%PATH%

set CROSS_COMPILE=arm-none-eabi-
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

cd %HOME%/../../repo_SayCV-RTEMS-SAM9X25/SayCVmxe
set HOME=%cd%
bash --login -i -c "mkdir -p usr/installed"
cd usr/installed && touch check-requirements
cd ../../
rem bash --login -i -c "make AT91Bootstrap-SAM9X25"

rem pause
rem exit


cd %ORIGIN_HOME%
set PATH=%HOME%/../../repo_SayCV-RTEMS-SAM9X25/SayCVmxe/usr/i686-pc-mingw32/bin;%PATH%

set CROSS_COMPILE=arm-rtemseabi4.11-
set ERASE_FCT=del /F
set CFLAGS= -DCFG_BRD_SP_ONE

make clean
echo Compile Bootstrap for sam9x25
if not exist .config (
cd board/at91sam9x5ek
set HOME=%cd%
bash --login -i -c "make at91sam9x5nf_defconfig"
cd ../.. )
set HOME=%cd%
bash --login -i -c "make"
pause
exit
set SRC_PATH=%cd%
echo Copy Files To Dest...
set DEST_PATH="C:/Docume~1/xiaoyc00181/×ÀÃæ/2012-5-15/AT91SAM9x5/Demos"
cd /d %DEST_PATH%
copy "%SRC_PATH%\binaries\at91sam9x5ek-nandflashboot-3.1.bin"

pause