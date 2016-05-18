@echo off

set str1=%cd%
cd ..
set str2=%cd%

set tmp1=%str1%
set tmp2=%str2%
::将str1复制到str
:next1
::标签，用于goto跳转
::注意与注释语句的区别，注释用两个冒号开头，标签则为一个冒号
if not "%tmp2%"=="" (
::判断str是不是空串，如果不是则执行下边的语句
set /a num1+=1
set /a num2+=1
::算术运算，使num的值自增1，相当于num++或者++num语句
set "tmp1=%tmp1:~1%"
set "tmp2=%tmp2:~1%"
::截取字符串，赋给自身
goto next1
::跳转到next1标签
::这里利用goto和标签，构成循环结构
)

set "tmp1=%tmp1:~1%"

cd %tmp1%

set prjName=%tmp1%
title  ranwei693532@163.com    %prjName%正在清理中...
echo 正在清除%prjName%工程,请稍等......


rmdir /S /Q .\MDK_prj\DebugConfig
del /f /s /q .\MDK_prj\Listings\*
del /f /s /q .\MDK_prj\Objects\*.*

del /f /s /q .\MDK_prj\JLinkLog.txt
del /f /s /q .\MDK_prj\JLinkSettings.ini
del /f /s /q .\MDK_prj\%prjName%.bin
del /f /s /q .\MDK_prj\%prjName%.uvguix.%USERNAME%

echo 清除%prjName%工程完成!
echo. & pause
