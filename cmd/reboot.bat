@echo off & setlocal enabledelayedexpansion
set count=0
set current=0
:step
::��numֵ����һ��ѭ����ʱ�䣬��λ��S
set/a num=120
set/a count+=1

for /l %%a in (!num! -1 1) DO (
 echo ʣ��ʱ��: [%%a]
 set/a current=count
 if not %current% == 0 echo.�� [%current%] ��
 timeout /t 1 /nobreak>nul & cls
)
@adb reboot || echo ����ǰ��ѭ��%count%�� && pause
echo.��ѭ��%count%��
::��"%count%"=="2000" �������ѭ������
if "%count%"=="2000" pause&&echo.ѭ��2000������

goto step