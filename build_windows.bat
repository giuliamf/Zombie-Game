@echo off
REM Script para compilar o Zombie Game no Windows
REM Requer: CMake, MinGW-w64 ou Visual Studio, e SDL2 libraries

echo ========================================
echo   Zombie Game - Build Script (Windows)
echo ========================================
echo.

REM Verifica se CMake está instalado
where cmake >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo [ERRO] CMake nao encontrado! Instale o CMake e adicione ao PATH.
    echo Download: https://cmake.org/download/
    pause
    exit /b 1
)

REM Cria diretório de build
if not exist build mkdir build
cd build

echo [1/3] Configurando projeto com CMake...
echo.

REM Configura o projeto (ajuste o generator conforme necessário)
REM Para MinGW: -G "MinGW Makefiles"
REM Para Visual Studio 2022: -G "Visual Studio 17 2022"
REM Para Visual Studio 2019: -G "Visual Studio 16 2019"

cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERRO] Falha na configuracao do CMake!
    cd ..
    pause
    exit /b 1
)

echo.
echo [2/3] Compilando o projeto...
echo.

cmake --build . --config Release
if %ERRORLEVEL% NEQ 0 (
    echo [ERRO] Falha na compilacao!
    cd ..
    pause
    exit /b 1
)

echo.
echo [3/3] Build concluido com sucesso!
echo.
echo Executavel criado em: build\bin\ZombieGame.exe
echo.
echo Para executar o jogo:
echo   cd build\bin
echo   ZombieGame.exe
echo.

cd ..
pause

