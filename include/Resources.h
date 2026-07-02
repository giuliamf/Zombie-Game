#pragma once

#include <string>
#include <unordered_map>
#include "SDL_include.h"

class Resources {
public:
    // Retorna a fonte para o arquivo e tamanho dados.
    // A chave de cache é: "arquivo#tamanho", ex: "font/Callme.ttf#32"
    // A fonte é aberta uma única vez e reutilizada em chamadas subsequentes.
    static TTF_Font* GetFont(const std::string& file, int size);

    // Fecha e libera todas as fontes em cache.
    // Deve ser chamado antes de TTF_Quit().
    static void ClearFonts();

private:
    static std::unordered_map<std::string, TTF_Font*> fontTable;
};
