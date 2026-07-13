@echo off
REM Script para instalar SDL2 via MSYS2
REM Execute este script antes de compilar o jogo

echo ========================================
echo   Instalando SDL2 via MSYS2
echo ========================================
echo.

REM Verifica se MSYS2 está instalado
if not exist "C:\msys64\usr\bin\bash.exe" (
    echo [ERRO] MSYS2 nao encontrado em C:\msys64\
    echo.
    echo Por favor, instale o MSYS2 primeiro:
    echo https://www.msys2.org/
    pause
    exit /b 1
)

echo Abrindo terminal MSYS2 para instalar as bibliotecas SDL2...
echo.
echo Execute os seguintes comandos no terminal MSYS2 que vai abrir:
echo.
echo   pacman -Syu
echo   pacman -S mingw-w64-x86_64-SDL2
echo   pacman -S mingw-w64-x86_64-SDL2_image
echo   pacman -S mingw-w64-x86_64-SDL2_mixer
echo   pacman -S mingw-w64-x86_64-SDL2_ttf
echo   pacman -S mingw-w64-x86_64-cmake
echo   exit
echo.
echo Pressione qualquer tecla para abrir o terminal MSYS2...
pause >nul

C:\msys64\msys2_shell.cmd -mingw64 -defterm -no-start -c "echo 'Execute os comandos acima para instalar SDL2'; exec bash"

echo.
echo Apos instalar as bibliotecas, feche o terminal MSYS2 e execute:
echo   build_windows.bat
echo.
pause
