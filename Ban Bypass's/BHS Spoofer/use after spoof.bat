@echo off
color 9

echo ======================================================================================
echo                                   8yke Cleaner
echo ======================================================================================
echo This script attempts to clean all of Rec Room's data from your computer.
echo Please run this WITHOUT administrator rights as elevated permissions may cause issues.
echo ======================================================================================

echo.
echo Deleting Rec Room LocalLow data...
rmdir /s /q "C:\Users\%USERNAME%\AppData\LocalLow\Against Gravity"

echo Deleting Rec Room temp files...
rmdir /s /q "%LocalAppData%\Temp\RecRoom"
rmdir /s /q "%LocalAppData%\Temp\Against Gravity"

echo Deleting Rec Room shortcuts and recent files...
del /s /q "%AppData%\Microsoft\Windows\Recent\RecRoom.lnk"
del /s /q "%AppData%\Microsoft\Windows\Start Menu\Programs\Steam\Rec Room.url"

echo Completed file deletion.
timeout /t 1 /nobreak > nul

echo ======================================================================================
echo Removing Rec Room's registry keys...
%windir%\system32\reg.exe import noRR.reg
echo Completed registry key removal.
echo ======================================================================================

echo Thank you for using the cleaner - by 8yke
echo ======================================================================================

echo.
echo Closing script in 5 seconds...
timeout /t 1 /nobreak > nul
echo Closing script in 4 seconds...
timeout /t 1 /nobreak > nul
echo Closing script in 3 seconds...
timeout /t 1 /nobreak > nul
echo Closing script in 2 seconds...
timeout /t 1 /nobreak > nul
echo Closing script in 1 second...
timeout /t 1 /nobreak > nul

exit
