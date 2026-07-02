# Zombie Game

Jogo de sobrevivência top-down desenvolvido em C++17 com SDL2.

O jogador deve sobreviver a ondas crescentes de zumbis. Ao eliminar todas as ondas, vence. Ao morrer, perde. Os resultados levam a uma tela de fim de jogo com opção de recomeçar.

---

## Sumário

- [Pré-requisitos](#pré-requisitos)
- [Como compilar](#como-compilar)
- [Como executar](#como-executar)
- [Controles](#controles)
- [Estrutura do projeto](#estrutura-do-projeto)
- [Arquitetura](#arquitetura)
- [Waves](#waves)
- [Recursos](#recursos)

---

## Pré-requisitos

| Dependência | Versão mínima | Instalação (macOS) |
|---|---|---|
| Clang / GCC | C++17 | `xcode-select --install` |
| SDL2 | 2.x | `brew install sdl2` |
| SDL2_image | — | `brew install sdl2_image` |
| SDL2_mixer | — | `brew install sdl2_mixer` |
| SDL2_ttf | — | `brew install sdl2_ttf` |

> **Nota:** o Homebrew pode instalar `sdl2-compat` (shim SDL3) em vez do SDL2 nativo em sistemas recentes. O jogo é compatível com ambos.

---

## Como compilar

Não há Makefile — compilar manualmente com:

```bash
clang++ -std=c++17 \
  -Iinclude \
  -I/opt/homebrew/include \
  -I/opt/homebrew/include/SDL2 \
  $(sdl2-config --cflags) \
  src/GameData.cpp src/Resources.cpp src/Text.cpp \
  src/State.cpp src/EndState.cpp src/TitleState.cpp \
  src/StageState.cpp src/Game.cpp \
  src/GameObject.cpp src/Component.cpp \
  src/Sprite.cpp src/SpriteRenderer.cpp \
  src/Animation.cpp src/Animator.cpp \
  src/Camera.cpp src/Character.cpp \
  src/Collider.cpp src/Collision.cpp \
  src/PlayerController.cpp \
  src/TileMap.cpp src/TileSet.cpp \
  src/Timer.cpp src/Vec2.cpp src/Rect.cpp \
  src/Music.cpp src/InputManager.cpp \
  src/Bullet.cpp src/Gun.cpp \
  src/Zombie.cpp src/AIController.cpp \
  src/WaveSpawner.cpp src/main.cpp \
  $(sdl2-config --libs) \
  -L/opt/homebrew/lib \
  -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
  -o jogo
```

---

## Como executar

Execute a partir da raiz do repositório (necessário para os caminhos de `Resources/` funcionarem):

```bash
./jogo
```

---

## Controles

### Tela de título

| Tecla | Ação |
|---|---|
| `SPACE` | Iniciar partida |
| `ESC` | Encerrar o jogo |
| `X` (janela) | Encerrar o jogo |

### Durante o jogo (StageState)

| Tecla | Ação |
|---|---|
| `W` | Mover para cima |
| `S` | Mover para baixo |
| `A` | Mover para a esquerda |
| `D` | Mover para a direita |
| Botão esquerdo do mouse | Atirar |
| `ESC` | Voltar à tela de título |

### Tela de fim de jogo (EndState)

| Tecla | Ação |
|---|---|
| `SPACE` | Jogar novamente (volta à tela de título) |
| `ESC` | Encerrar o jogo |
| `X` (janela) | Encerrar o jogo |

---

## Estrutura do projeto

```
Zombie-Game/
├── include/              # Headers (.h)
│   ├── State.h           # Classe base abstrata — State Stack
│   ├── Game.h            # Singleton do jogo, gerencia State Stack
│   ├── TitleState.h      # Tela de título
│   ├── StageState.h      # Estado de gameplay
│   ├── EndState.h        # Tela de fim de jogo
│   ├── GameData.h        # Dados compartilhados entre estados
│   ├── Text.h            # Componente de texto (SDL_ttf)
│   ├── Resources.h       # Cache de fontes TTF
│   ├── GameObject.h      # Entidade do jogo
│   ├── Component.h       # Componente base
│   ├── Character.h       # Componente do jogador
│   ├── Zombie.h          # Componente de zumbi
│   ├── AIController.h    # IA de perseguição
│   ├── WaveSpawner.h     # Gerenciador de ondas
│   ├── Gun.h             # Componente da arma
│   ├── Bullet.h          # Componente de projétil
│   ├── Sprite.h          # Textura + frame
│   ├── SpriteRenderer.h  # Componente de renderização
│   ├── Animator.h        # Animação por frames
│   ├── Animation.h       # Definição de animação
│   ├── Collider.h        # Caixa de colisão
│   ├── Collision.h       # Detecção AABB
│   ├── TileMap.h         # Mapa de tiles
│   ├── TileSet.h         # Conjunto de tiles
│   ├── Camera.h          # Câmera 2D
│   ├── InputManager.h    # Entrada de teclado e mouse
│   ├── Music.h           # Música de fundo
│   ├── Timer.h           # Temporizador
│   ├── Vec2.h            # Vetor 2D
│   ├── Rect.h            # Retângulo
│   └── SDL_include.h     # Centraliza includes SDL
│
├── src/                  # Implementações (.cpp)
│   └── ...               # Espelho de include/
│
├── Resources/
│   ├── img/              # Sprites e fundos
│   │   ├── background.png
│   │   ├── Player.png
│   │   ├── Enemy.png
│   │   ├── Gun.png
│   │   ├── Bullet.png
│   │   ├── Tileset.png
│   │   ├── Title.png
│   │   ├── Win.png
│   │   └── Lose.png
│   ├── audio/            # Efeitos e músicas
│   │   ├── BGM.wav
│   │   ├── endStateWin.ogg
│   │   ├── endStateLose.ogg
│   │   ├── PumpAction.mp3
│   │   └── ...
│   ├── font/
│   │   └── font.ttf      # Fonte usada nos textos
│   └── map/
│       └── map.txt       # Mapa de tiles
│
└── README.md
```

---

## Arquitetura

### State Stack

O jogo utiliza uma pilha de estados (`std::stack<std::unique_ptr<State>>`), gerenciada por `Game`. Cada estado implementa a interface abstrata `State`:

```
State  (abstrata)
├── TitleState   — tela inicial
├── StageState   — partida em andamento
└── EndState     — resultado (vitória ou derrota)
```

**Ciclo de vida por estado:**

| Método | Quando é chamado |
|---|---|
| `Start()` | Uma vez, quando o estado vai ao topo da pilha |
| `Update(dt)` | Todo frame, enquanto for o topo |
| `Render()` | Todo frame, após `Update` |
| `Pause()` | Quando outro estado é empilhado sobre este |
| `Resume()` | Quando o estado acima é desempilhado |
| `LoadAssets()` | Chamado pelo construtor de cada estado |

**Transições:**

```
main
 └─ game.Push(new TitleState())
     └─ game.Run()
         │
         TitleState
         ├── ESC          → quitRequested = true     → encerra
         └── SPACE        → Push(new StageState())   → empilha
                              │
                              StageState
                              ├── ESC          → popRequested = true   → volta a TitleState
                              ├── player morreu → Push(new EndState()) → empilha
                              └── all waves done → Push(new EndState()) → empilha
                                                     │
                                                     EndState
                                                     ├── ESC   → quitRequested = true
                                                     └── SPACE → popRequested = true
                                                                  Push(new TitleState())
```

### Sistema de componentes

`GameObject` é um contêiner de `Component`. Cada comportamento é um componente separado:

```
GameObject
├── SpriteRenderer   → renderiza sprite com câmera
├── Animator         → anima por sequência de frames
├── Collider         → caixa de colisão AABB
├── Character        → movimento, HP, morte do jogador
├── PlayerController → lê input e aciona Character
├── Gun              → aponta para o mouse, dispara Bullets
├── Zombie           → comportamento de zumbi
├── AIController     → perseguição ao jogador
├── WaveSpawner      → spawna zumbis em ondas
└── Text             → renderiza texto via SDL_ttf
```

### GameData

`GameData::playerVictory` (estático) é o canal de comunicação entre `StageState` e `EndState`. É escrito pelo `StageState` e lido pelo construtor de `EndState` para decidir qual fundo e música exibir.

---

## Waves

| Wave | Zumbis | Intervalo de spawn |
|---|---|---|
| 1 | 5 | 1,0 s |
| 2 | 10 | 0,7 s |
| 3 | 15 | 0,5 s |
| 4 | 20 | 0,4 s |
| 5 | 30 | 0,3 s |

Ao concluir todas as 5 waves, `StageState` detecta `WaveSpawner::IsWaveComplete()` e transiciona para `EndState` com `playerVictory = true`.

---

## Recursos

| Asset | Uso |
|---|---|
| `img/background.png` | Fundo do mapa de jogo |
| `img/Player.png` | Spritesheet do jogador (3×4 frames) |
| `img/Enemy.png` | Spritesheet do zumbi (3×2 frames) |
| `img/Gun.png` | Spritesheet da arma (3×2 frames) |
| `img/Bullet.png` | Projétil |
| `img/Tileset.png` | Tiles do mapa (64×64 px) |
| `img/Title.png` | Fundo da tela de título |
| `img/Win.png` | Fundo da tela de vitória |
| `img/Lose.png` | Fundo da tela de derrota |
| `audio/BGM.wav` | Música do gameplay |
| `audio/endStateWin.ogg` | Música de vitória |
| `audio/endStateLose.ogg` | Música de derrota |
| `font/font.ttf` | Fonte TrueType para textos na tela |
| `map/map.txt` | Arquivo de mapa (índices de tiles) |

---

*Giulia Ferreira — UnB 200018795*
