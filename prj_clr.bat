@echo off

set str1=%cd%
cd ..
set str2=%cd%

set tmp1=%str1%
set tmp2=%str2%
::��str1���Ƶ�str
:next1
::��ǩ������goto��ת
::ע����ע����������ע��������ð�ſ�ͷ����ǩ��Ϊһ��ð��
if not "%tmp2%"=="" (
::�ж�str�ǲ��ǿմ������������ִ���±ߵ����
set /a num1+=1
set /a num2+=1
::�������㣬ʹnum��ֵ����1���൱��num++����++num���
set "tmp1=%tmp1:~1%"
set "tmp2=%tmp2:~1%"
::��ȡ�ַ�������������
goto next1
::��ת��next1��ǩ
::��������goto�ͱ�ǩ������ѭ���ṹ
)

set "tmp1=%tmp1:~1%"

cd %tmp1%

set prjName=%tmp1%
title  ranwei693532@163.com    %prjName%����������...
echo �������%prjName%����,���Ե�......


rmdir /S /Q .\MDK_prj\DebugConfig
del /f /s /q .\MDK_prj\Listings\*
del /f /s /q .\MDK_prj\Objects\*.*

del /f /s /q .\MDK_prj\JLinkLog.txt
del /f /s /q .\MDK_prj\JLinkSettings.ini
del /f /s /q .\MDK_prj\%prjName%.bin
del /f /s /q .\MDK_prj\%prjName%.uvguix.%USERNAME%

echo ���%prjName%�������!
echo. & pause
