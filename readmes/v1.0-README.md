# Trabalho 1 - Introdução ao Desenvolvimento de Jogos

## Identificação

**Disciplina:** Introdução ao Desenvolvimento de Jogos  
**Trabalho:** Entrega 1 - Estrutura Básica de Engine  
**Aluna:** Giulia Moura Ferreira  
**Matrícula:** 200018795

---

## Descrição do Projeto

Este projeto implementa a estrutura básica de uma engine de jogos utilizando a biblioteca SDL2 e suas extensões. O objetivo desta primeira entrega é estabelecer uma base sólida de código orientado a objetos, com foco na arquitetura e organização do projeto, sem implementação de gameplay.

O programa abre uma janela gráfica de 1200x900 pixels, exibe um plano de fundo e reproduz uma música ambiente em loop. O sistema está preparado para receber eventos do usuário e encerrar corretamente quando solicitado.

---

## Objetivos do Trabalho

Os principais objetivos desta entrega são:

1. Configurar corretamente o ambiente de desenvolvimento com SDL2 no macOS
2. Implementar uma estrutura de classes bem organizada seguindo princípios de orientação a objetos
3. Criar um game loop funcional que controla a execução do programa
4. Gerenciar recursos gráficos e de áudio de forma adequada
5. Implementar o padrão de projeto Singleton para a classe principal
6. Estabelecer uma base de código que será expandida nas próximas entregas

---

## Tecnologias Utilizadas

- **Linguagem:** C++
- **Bibliotecas:**
  - SDL2 (Simple DirectMedia Layer) - Gerenciamento de janelas, renderização e eventos
  - SDL2_image - Carregamento de imagens em diversos formatos
  - SDL2_mixer - Reprodução de áudio e música
- **Plataforma:** macOS
- **IDE:** Visual Studio Code
- **Compilador:** g++ (GNU C++ Compiler)

---

## Estrutura do Projeto

```
Zombie-Game/
├── include/              # Arquivos de cabeçalho (.h)
│   ├── Game.h           # Classe principal (Singleton)
│   ├── State.h          # Estado do jogo
│   ├── Sprite.h         # Gerenciamento de sprites
│   ├── Music.h          # Gerenciamento de música
│   └── SDL_include.h    # Inclusões da SDL
├── src/                 # Arquivos de implementação (.cpp)
│   ├── main.cpp         # Ponto de entrada do programa
│   ├── Game.cpp         # Implementação da classe Game
│   ├── State.cpp        # Implementação da classe State
│   ├── Sprite.cpp       # Implementação da classe Sprite
│   └── Music.cpp        # Implementação da classe Music
├── Resources/           # Recursos do jogo (fornecidos)
│   ├── img/            # Imagens e sprites
│   ├── audio/          # Músicas e efeitos sonoros
│   ├── font/           # Fontes
│   └── map/            # Mapas
└── README.md           # Este arquivo
```

---

## Descrição das Classes

### Game (Singleton)

A classe `Game` é o núcleo da engine e implementa o padrão Singleton, garantindo que apenas uma instância exista durante toda a execução do programa.

**Responsabilidades:**
- Inicializar e finalizar os subsistemas da SDL
- Criar e gerenciar a janela do jogo
- Criar e gerenciar o renderer (responsável pela renderização gráfica)
- Controlar o game loop principal
- Fornecer acesso global à instância única através do método `GetInstance()`

**Métodos principais:**
- `GetInstance()`: Retorna a instância única da classe
- `Run()`: Executa o game loop principal
- `GetRenderer()`: Retorna o renderer SDL para uso em outras classes
- `GetState()`: Retorna o estado atual do jogo

### State

A classe `State` representa o estado atual do jogo e gerencia os elementos que compõem a cena.

**Responsabilidades:**
- Carregar os recursos (assets) necessários
- Atualizar a lógica do jogo a cada frame
- Renderizar os elementos na tela
- Detectar quando o usuário solicita o encerramento do programa

**Métodos principais:**
- `LoadAssets()`: Carrega imagem de fundo e música
- `Update(float dt)`: Atualiza o estado (processa eventos)
- `Render()`: Renderiza o plano de fundo
- `QuitRequested()`: Indica se o usuário solicitou o encerramento

### Sprite

A classe `Sprite` encapsula o gerenciamento de imagens e texturas.

**Responsabilidades:**
- Carregar imagens de arquivos
- Armazenar texturas na memória da GPU
- Renderizar imagens na tela em posições específicas
- Gerenciar recortes (clipping) de sprites

**Métodos principais:**
- `Open(const std::string& file)`: Carrega uma imagem
- `Render(int x, int y)`: Desenha a imagem na posição especificada
- `SetClip(int x, int y, int w, int h)`: Define área de recorte
- `GetWidth()` / `GetHeight()`: Retornam dimensões da imagem
- `IsOpen()`: Verifica se a imagem foi carregada com sucesso

### Music

A classe `Music` gerencia a reprodução de músicas de fundo.

**Responsabilidades:**
- Carregar arquivos de música
- Reproduzir música em loop ou número específico de vezes
- Parar a reprodução
- Liberar recursos de áudio

**Métodos principais:**
- `Open(const std::string& file)`: Carrega um arquivo de música
- `Play(int times = -1)`: Reproduz a música (padrão: loop infinito)
- `Stop()`: Para a reprodução
- `IsOpen()`: Verifica se a música foi carregada com sucesso

---

## Como Compilar e Executar

### Pré-requisitos

Certifique-se de ter instalado:
- Xcode Command Line Tools
- SDL2, SDL2_image e SDL2_mixer (via Homebrew)

```bash
brew install sdl2 sdl2_image sdl2_mixer
```

### Compilação

No terminal, navegue até o diretório do projeto e execute:

```bash
g++ -std=c++11 -Iinclude \
    src/*.cpp \
    -F/Library/Frameworks \
    -framework SDL2 \
    -framework SDL2_image \
    -framework SDL2_mixer \
    -o jogo
```

### Execução

Após a compilação bem-sucedida, execute:

```bash
./jogo
```

O programa abrirá uma janela de 1200x900 pixels com o título contendo o nome e matrícula da aluna, exibirá o plano de fundo e iniciará a reprodução da música ambiente.

Para encerrar o programa, clique no botão de fechar da janela ou pressione Alt+F4 (Command+Q no macOS).

---

## Observações Finais

Esta primeira entrega tem caráter **estrutural e preparatório**. O foco está na organização do código, na correta utilização da SDL2 e na implementação de padrões de projeto adequados.

Não há implementação de gameplay, mecânicas de jogo ou interatividade além do encerramento do programa. Estes elementos serão desenvolvidos nas próximas entregas, utilizando esta base como fundação.

A arquitetura implementada foi projetada para ser extensível e facilitar a adição de novos recursos, como:
- Sistema de entrada (teclado e mouse)
- Gerenciamento de múltiplos estados
- Sistema de entidades e componentes
- Detecção de colisões
- Sistema de partículas
- E outros elementos que serão incorporados ao longo da disciplina

---

**Data de Entrega:** 10 de abril, 2026  
**Versão:** 1.0
