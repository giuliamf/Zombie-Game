#include "Game.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    // Inicializar seed do random para spawns aleatórios
    srand(static_cast<unsigned int>(time(NULL)));
    
    Game& game = Game::GetInstance();
    game.Run();
    return 0;
}