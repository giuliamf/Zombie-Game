<div align="center">

# 🧟 Zombie Game

### Jogo de sobrevivência top-down desenvolvido em C++17 com SDL2

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![SDL2](https://img.shields.io/badge/SDL-2.0-green.svg)](https://www.libsdl.org/)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS-lightgrey.svg)](https://github.com)

*Sobreviva a ondas crescentes de zumbis. Elimine todos para vencer. Morra e perca. Simples assim.*

[🎮 Como Jogar](#-como-executar) • [🛠️ Compilar](#-como-compilar) • [📖 Documentação](#-documentação-completa)

</div>

---

## 📋 Sumário

- [🎯 Sobre o Jogo](#-sobre-o-jogo)
- [🎮 COMO JOGAR (Executável Pronto)](#-como-jogar-executável-pronto)
- [🎯 Controles](#-controles)
- [🌊 Sistema de Waves](#-sistema-de-waves)
- [📁 Estrutura do Projeto](#-estrutura-do-projeto)
- [🏗️ Arquitetura](#️-arquitetura)
- [🎨 Recursos](#-recursos)
- [🛠️ Para Desenvolvedores](#️-para-desenvolvedores)
- [📖 Documentação Completa](#-documentação-completa)

---

## 🎯 Sobre o Jogo

Zombie Game é um shooter top-down onde você deve sobreviver a **5 ondas progressivamente mais difíceis** de zumbis. Use WASD para se mover e o mouse para atirar. Cada wave aumenta o número de inimigos e reduz o tempo entre spawns.

**Objetivo:** Elimine todos os zumbis de todas as waves para vencer!

---

## 🎮 COMO JOGAR (Executável Pronto)

> **✨ O jogo já está compilado e pronto para jogar! Não é necessário compilar nada.**

### 🪟 Windows

1. **Localize o executável:**
   ```
   build\bin\ZombieGame.exe
   ```

2. **Execute de uma das formas:**
   
   **Opção A - Duplo Clique (Mais Fácil):**
   - Navegue até a pasta `build\bin\`
   - Dê **duplo clique** em `ZombieGame.exe`
   - O jogo iniciará automaticamente!

   **Opção B - Terminal:**
   ```cmd
   cd build\bin
   ZombieGame.exe
   ```

3. **Pronto!** O jogo deve abrir e você pode começar a jogar.

### 🍎 macOS

1. **Localize o executável:**
   ```
   build/bin/ZombieGame
   ```

2. **Execute via terminal:**
   ```bash
   cd build/bin
   ./ZombieGame
   ```

3. **Pronto!** O jogo deve abrir e você pode começar a jogar.

### ⚠️ Importante

- O executável **DEVE** estar na pasta `build/bin/` junto com a pasta `Resources/`
- A estrutura correta é:
  ```
  build/
  └── bin/
      ├── ZombieGame.exe (ou ZombieGame no macOS)
      └── Resources/
          ├── img/
          ├── audio/
          ├── font/
          └── map/
  ```
- Se você mover o executável, mova também a pasta `Resources/` junto

### 🐛 Problemas ao Executar?

**Windows - "DLL não encontrada":**
- Certifique-se de que `C:\msys64\mingw64\bin` está no PATH do sistema
- Ou copie as DLLs necessárias para a pasta `build\bin\`:
  - SDL2.dll
  - SDL2_image.dll
  - SDL2_mixer.dll
  - SDL2_ttf.dll

**macOS - "Não é possível abrir":**
- Execute: `chmod +x build/bin/ZombieGame`
- Ou vá em Preferências do Sistema → Segurança e permita a execução

---

## 💻 Pré-requisitos (Apenas para Compilar)

> **📌 Nota:** Se você só quer jogar, pule esta seção! O executável já está pronto em `build/bin/`.

Esta seção é apenas para quem deseja **recompilar** o jogo do zero.

### 🪟 Windows

| Ferramenta | Instalação |
|------------|------------|
| **MSYS2** | [Download](https://www.msys2.org/) |
| **Dependências SDL2** | Abra o terminal MSYS2 MinGW 64-bit e execute: |

```bash
# Atualizar sistema
pacman -Syu

# Instalar compilador e ferramentas
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-make

# Instalar SDL2 e extensões
pacman -S mingw-w64-x86_64-SDL2
pacman -S mingw-w64-x86_64-SDL2_image
pacman -S mingw-w64-x86_64-SDL2_mixer
pacman -S mingw-w64-x86_64-SDL2_ttf
```

**Configurar PATH:**
Adicione `C:\msys64\mingw64\bin` às variáveis de ambiente do Windows.

### 🍎 macOS

```bash
# Instalar Xcode Command Line Tools
xcode-select --install

# Instalar Homebrew (se ainda não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependências
brew install cmake sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

---

## 🛠️ Para Desenvolvedores

> **📌 Esta seção é apenas para quem deseja recompilar o código-fonte.**
> **Se você só quer jogar, use o executável em `build/bin/` conforme explicado acima.**

### 🛠️ Como Compilar

#### 🎯 Método 1: Scripts Automáticos (Recomendado)

#### 🪟 Windows

```cmd
build_windows.bat
```

#### 🍎 macOS

```bash
chmod +x build_macos.sh
./build_macos.sh
```

---

### 🔧 Método 2: CMake Manual (Multiplataforma)

#### 🪟 Windows

```cmd
# Criar diretório de build
mkdir build
cd build

# Configurar projeto
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

# Compilar
cmake --build . --config Release

# Executar
cd bin
ZombieGame.exe
```

#### 🍎 macOS

```bash
# Criar diretório de build
mkdir build
cd build

# Configurar projeto
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compilar
cmake --build . --config Release

# Executar
cd bin
./ZombieGame
```

---

### ⚙️ Método 3: Compilação Direta (Apenas macOS)

Para compilar sem CMake, execute todos os comandos abaixo **em uma única linha** ou use `\` para quebrar linhas:

```bash
clang++ -std=c++17 \
  -Iinclude \
  -I/opt/homebrew/include \
  -I/opt/homebrew/include/SDL2 \
  $(sdl2-config --cflags) \
  src/GameData.cpp \
  src/Resources.cpp \
  src/Text.cpp \
  src/State.cpp \
  src/EndState.cpp \
  src/TitleState.cpp \
  src/StageState.cpp \
  src/Game.cpp \
  src/GameObject.cpp \
  src/Component.cpp \
  src/Sprite.cpp \
  src/SpriteRenderer.cpp \
  src/Animation.cpp \
  src/Animator.cpp \
  src/Camera.cpp \
  src/Character.cpp \
  src/Collider.cpp \
  src/Collision.cpp \
  src/PlayerController.cpp \
  src/TileMap.cpp \
  src/TileSet.cpp \
  src/Timer.cpp \
  src/Vec2.cpp \
  src/Rect.cpp \
  src/Music.cpp \
  src/InputManager.cpp \
  src/Bullet.cpp \
  src/Gun.cpp \
  src/Zombie.cpp \
  src/AIController.cpp \
  src/WaveSpawner.cpp \
  src/main.cpp \
  $(sdl2-config --libs) \
  -L/opt/homebrew/lib \
  -lSDL2_image \
  -lSDL2_mixer \
  -lSDL2_ttf \
  -o jogo
```

Depois execute:

```bash
./jogo
```

> **Nota:** Este método requer que você execute o jogo a partir da raiz do projeto para que os caminhos de `Resources/` funcionem.

---

#### 🎮 Como Executar Após Compilar

**Após Compilação com CMake:**

🪟 **Windows:**
```cmd
cd build\bin
ZombieGame.exe
```

🍎 **macOS:**
```bash
cd build/bin
./ZombieGame
```

**Após Compilação Direta (macOS):**
```bash
./jogo
```

---

## 🎯 Controles

### 🎬 Tela de Título

| Tecla | Ação |
|-------|------|
| `SPACE` | Iniciar partida |
| `ESC` | Sair do jogo |

### 🎮 Durante o Jogo

| Controle | Ação |
|----------|------|
| `W` | Mover para cima |
| `A` | Mover para a esquerda |
| `S` | Mover para baixo |
| `D` | Mover para a direita |
| `Mouse` | Mirar |
| `Botão Esquerdo` | Atirar |
| `ESC` | Voltar ao menu |

### 🏁 Tela de Fim de Jogo

| Tecla | Ação |
|-------|------|
| `SPACE` | Jogar novamente |
| `ESC` | Sair do jogo |

---

## 📁 Estrutura do Projeto

```
Zombie-Game/
│
├── 📂 include/                    # Headers (.h)
│   ├── State.h                    # Sistema de estados
│   ├── Game.h                     # Gerenciador principal
│   ├── TitleState.h               # Tela de título
│   ├── StageState.h               # Gameplay
│   ├── EndState.h                 # Tela de fim
│   ├── GameObject.h               # Entidades do jogo
│   ├── Component.h                # Sistema de componentes
│   ├── Character.h                # Jogador
│   ├── Zombie.h                   # Inimigos
│   ├── Gun.h                      # Arma
│   ├── Bullet.h                   # Projéteis
│   ├── WaveSpawner.h              # Sistema de ondas
│   └── ...                        # Outros componentes
│
├── 📂 src/                        # Implementações (.cpp)
│   └── ...                        # Arquivos correspondentes
│
├── 📂 Resources/                  # Assets do jogo
│   ├── 🖼️ img/                   # Sprites e imagens
│   │   ├── Player.png             # Spritesheet do jogador (3×4)
│   │   ├── Enemy.png              # Spritesheet do zumbi (3×2)
│   │   ├── Gun.png                # Spritesheet da arma (3×2)
│   │   ├── Bullet.png             # Projétil
│   │   ├── Title.png              # Tela de título
│   │   ├── Win.png                # Tela de vitória
│   │   └── Lose.png               # Tela de derrota
│   │
│   ├── 🔊 audio/                 # Sons e músicas
│   │   ├── BGM.wav                # Música de fundo
│   │   ├── PumpAction.mp3         # Som de tiro
│   │   ├── endStateWin.ogg        # Música de vitória
│   │   └── endStateLose.ogg       # Música de derrota
│   │
│   ├── 🔤 font/                  # Fontes
│   │   └── font.ttf               # Fonte principal
│   │
│   └── 🗺️ map/                   # Mapas
│       └── map.txt                # Layout do mapa
│
├── 📂 build/                      # Arquivos de compilação (gerado)
│   └── bin/                       # Executável final
│       ├── ZombieGame.exe         # Windows
│       ├── ZombieGame             # macOS
│       └── Resources/             # Cópia dos assets
│
├── 📄 CMakeLists.txt              # Configuração CMake
├── 📄 build_windows.bat           # Script de build Windows
├── 📄 build_macos.sh              # Script de build macOS
├── 📄 README.md                   # Este arquivo
├── 📄 BUILD.md                    # Documentação detalhada
├── 📄 WINDOWS_BUILD.md            # Guia específico Windows
└── 📄 GUIA_RAPIDO.md              # Guia de início rápido
```

---

## 🏗️ Arquitetura

### 🔄 State Stack Pattern

O jogo utiliza uma **pilha de estados** para gerenciar diferentes telas:

```
┌─────────────────────────────────────┐
│          State (abstrata)           │
└─────────────────────────────────────┘
                  ▲
                  │
        ┌─────────┼─────────┐
        │         │         │
   TitleState  StageState  EndState
   (Menu)      (Gameplay)  (Resultado)
```

**Fluxo de Estados:**

```
Início
  │
  ├─► TitleState (Menu Principal)
  │     │
  │     ├─ SPACE ──► StageState (Jogo)
  │     │              │
  │     │              ├─ Player Morreu ──► EndState (Derrota)
  │     │              │                      │
  │     │              └─ Waves Completas ──► EndState (Vitória)
  │     │                                      │
  │     └─────────────────────────────────────┘
  │                    SPACE (Jogar Novamente)
  │
  └─ ESC ──► Sair
```

### 🧩 Sistema de Componentes

Cada `GameObject` é composto por múltiplos `Component`s:

```
GameObject
├── SpriteRenderer    → Renderiza sprite
├── Animator          → Anima frames
├── Collider          → Detecta colisões
├── Character         → Lógica do jogador
├── PlayerController  → Controla input
├── Gun               → Gerencia arma
├── Zombie            → Comportamento inimigo
├── AIController      → IA de perseguição
└── WaveSpawner       → Spawna ondas
```

### 📊 Ciclo de Vida

Cada componente implementa:

| Método | Descrição |
|--------|-----------|
| `Start()` | Inicialização (chamado uma vez) |
| `Update(dt)` | Atualização lógica (todo frame) |
| `Render()` | Renderização (todo frame) |
| `NotifyCollision()` | Resposta a colisões |

---

## 🌊 Sistema de Waves

O jogo possui **5 ondas progressivas** de dificuldade crescente:

| 🌊 Wave | 🧟 Zumbis | ⏱️ Intervalo | 💀 Dificuldade |
|---------|-----------|--------------|----------------|
| **1** | 5 | 1.0s | ⭐ Fácil |
| **2** | 10 | 0.7s | ⭐⭐ Médio |
| **3** | 15 | 0.5s | ⭐⭐⭐ Difícil |
| **4** | 20 | 0.4s | ⭐⭐⭐⭐ Muito Difícil |
| **5** | 30 | 0.3s | ⭐⭐⭐⭐⭐ Extremo |

**Mecânica:**
- Cada wave deve ser completamente eliminada antes da próxima começar
- O intervalo entre spawns diminui a cada wave
- Sobreviva a todas as 5 waves para vencer!

---

## 🎨 Recursos

### 🖼️ Sprites

| Asset | Descrição | Dimensões |
|-------|-----------|-----------|
| `Player.png` | Spritesheet do jogador | 3×4 frames |
| `Enemy.png` | Spritesheet do zumbi | 3×2 frames |
| `Gun.png` | Spritesheet da arma | 3×2 frames |
| `Bullet.png` | Projétil | Single frame |
| `Tileset.png` | Tiles do mapa | 64×64 px |
| `Title.png` | Tela de título | Full screen |
| `Win.png` | Tela de vitória | Full screen |
| `Lose.png` | Tela de derrota | Full screen |

### 🔊 Áudio

| Asset | Tipo | Uso |
|-------|------|-----|
| `BGM.wav` | Música | Loop durante gameplay |
| `PumpAction.mp3` | SFX | Som de disparo |
| `endStateWin.ogg` | Música | Tela de vitória |
| `endStateLose.ogg` | Música | Tela de derrota |
| `Hit0.wav`, `Hit1.wav` | SFX | Sons de impacto |
| `Dead.wav` | SFX | Morte do jogador |

### 🔤 Fontes

| Asset | Uso |
|-------|-----|
| `font.ttf` | Textos e UI |

---

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C++17
- **Biblioteca Gráfica:** SDL2
- **Extensões SDL:** SDL2_image, SDL2_mixer, SDL2_ttf
- **Build System:** CMake 3.15+
- **Compiladores:** GCC, Clang, MinGW-w64

---

## 📝 Notas de Desenvolvimento

### Compatibilidade

- ✅ Windows 10/11 (via MSYS2/MinGW)
- ✅ macOS (Intel e Apple Silicon)
- ✅ SDL2 e SDL3-compat

### Requisitos de Sistema

- **CPU:** Dual-core 2.0 GHz ou superior
- **RAM:** 512 MB
- **GPU:** Suporte a OpenGL 2.0
- **Espaço:** ~50 MB

---

<div align="center">

**Aluna:** Giulia Moura Ferreira  
**Matrícula:** 200018795  
**Instituição:** Universidade de Brasília  
**Disciplina:** Introdução ao Desenvolvimento de Jogos

---

