#include "Game.h"
#include "InputManager.h"

#include <iostream>

// variável estática 
Game* Game::instance = nullptr;

// verifica se já existe um jogo, se não existir, cria um novo e retorna uma ref para ele
Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game(
            "Giulia Moura - 200018795",
            1200,
            900
        );
    }
    return *instance;
}

// para evitar lixo de memoria
Game::Game(const std::string& title, int width, int height)
    : window(nullptr), renderer(nullptr), storedState(nullptr), frameStart(0)
{
    if (instance != nullptr) {
        std::cerr << "Erro: Game já foi instanciado!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    instance = this;

    // inicia video, audio e temporizador
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Erro SDL_Init: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // usar png e jpg
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cerr << "Erro IMG_Init: " << IMG_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // inicializa suporte a fontes TrueType
    if (TTF_Init() != 0) {
        std::cerr << "Erro TTF_Init: " << TTF_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // audio: ativa musicas mp3 e ogg
    if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0) {
        std::cerr << "Erro Mix_Init: " << Mix_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // audio: inicializa o audio
    if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        1024
    ) != 0) {
        std::cerr << "Erro Mix_OpenAudio: " << Mix_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // reserva os canais de som 
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (window == nullptr) {
        std::cerr << "Erro SDL_CreateWindow: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // pega o melhor driver e usa a gpu
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr) {
        std::cerr << "Erro SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

}

// evitar vazamento de memoria
Game::~Game() {
    // libera todos os estados da pilha
    while (!stateStack.empty()) {
        stateStack.pop();
    }
    delete storedState;

    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetCurrentState() {
    return *stateStack.top();
}

// Armazena o estado para ser empilhado posteriormente — não empilha imediatamente
void Game::Push(State* state) {
    storedState = state;
}

// Calcula o delta time em segundos desde o último frame
float Game::CalculateDeltaTime() {
    Uint32 now = SDL_GetTicks();
    float dt = (now - frameStart) / 1000.0f;
    frameStart = now;
    return dt;
}

void Game::Run() {
    // Encerra imediatamente se nenhum estado foi fornecido via Push()
    if (storedState == nullptr) {
        return;
    }

    // Empilha o estado inicial e o inicia
    stateStack.emplace(storedState);
    storedState = nullptr;
    stateStack.top()->Start();

    // frameStart é definido APÓS Start() para não inflar o dt do primeiro frame
    // com o tempo gasto em carregamento de assets e inicialização de objetos
    frameStart = SDL_GetTicks();

    while (!stateStack.empty()
           && !GetCurrentState().QuitRequested()
           && !InputManager::GetInstance().QuitRequested()) {

        // 1. O topo pediu pop: desempilha e retoma o estado anterior
        if (GetCurrentState().PopRequested()) {
            stateStack.pop();
            if (!stateStack.empty()) {
                GetCurrentState().Resume();
            }
        }

        // 2. Há um novo estado aguardando: pausa o topo e empilha o novo
        //    Processado no mesmo frame que o pop, se ambos ocorrerem juntos
        if (storedState != nullptr) {
            if (!stateStack.empty()) {
                GetCurrentState().Pause();
            }
            stateStack.emplace(storedState);
            storedState = nullptr;
            stateStack.top()->Start();
        }

        // 3. Calcula delta time
        float dt = CalculateDeltaTime();

        // 4. Processa entradas
        InputManager::GetInstance().Update();

        // 5. Atualiza o estado do topo
        SDL_RenderClear(renderer);
        GetCurrentState().Update(dt);

        // 6. Renderiza o estado do topo
        GetCurrentState().Render();
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    // Encerramento: esvazia a pilha e descarta storedState pendente
    delete storedState;
    storedState = nullptr;
    while (!stateStack.empty()) {
        stateStack.pop();
    }
}
