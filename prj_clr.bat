@echo off

set prjName=STM32F4XX-OS
title  ranwei693532@163.com    %prjName%����������...
echo �������%prjName%����,���Ե�......


rmdir /S /Q .\MDK_prj\DebugConfig
del /f /s /q .\MDK_prj\Listings\*
del /f /s /q .\MDK_prj\Objects\*.*

del /f /s /q .\MDK_prj\JLinkLog.txt
del /f /s /q .\MDK_prj\JLinkSettings.ini
del /f /s /q .\MDK_prj\%prjName%.bin
del /f /s /q .\MDK_prj\%prjName%.uvguix.Administrator

echo ���%prjName%�������!
echo. & pause
