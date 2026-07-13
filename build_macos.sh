#!/bin/bash
# Script para compilar o Zombie Game no macOS
# Requer: CMake, Xcode Command Line Tools, e SDL2 libraries (via Homebrew)

echo "========================================"
echo "  Zombie Game - Build Script (macOS)"
echo "========================================"
echo ""

# Verifica se CMake está instalado
if ! command -v cmake &> /dev/null; then
    echo "[ERRO] CMake não encontrado! Instale com:"
    echo "  brew install cmake"
    exit 1
fi

# Verifica se as bibliotecas SDL2 estão instaladas
if ! brew list sdl2 &> /dev/null; then
    echo "[AVISO] SDL2 não encontrado. Instalando dependências..."
    echo ""
    brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
    if [ $? -ne 0 ]; then
        echo "[ERRO] Falha ao instalar SDL2!"
        exit 1
    fi
fi

# Cria diretório de build
mkdir -p build
cd build

echo "[1/3] Configurando projeto com CMake..."
echo ""

# Configura o projeto
cmake .. -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "[ERRO] Falha na configuração do CMake!"
    cd ..
    exit 1
fi

echo ""
echo "[2/3] Compilando o projeto..."
echo ""

# Compila
cmake --build . --config Release
if [ $? -ne 0 ]; then
    echo "[ERRO] Falha na compilação!"
    cd ..
    exit 1
fi

echo ""
echo "[3/3] Build concluído com sucesso!"
echo ""
echo "Executável criado em: build/bin/ZombieGame"
echo ""
echo "Para executar o jogo:"
echo "  cd build/bin"
echo "  ./ZombieGame"
echo ""

cd ..
