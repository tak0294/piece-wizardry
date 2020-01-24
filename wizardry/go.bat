call makeall.bat
chkpiece.exe
if "%ERRORLEVEL%"=="0" goto normal
if not "%ERRORLEVEL%"=="0" goto emulator

:normal
run wizardry
goto end

:emulator
emu\pffs.exe emu\piece.pfi -a wizardry.pex
cd emu
piemu.exe
cd ..
:end
