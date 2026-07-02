#include "Resources.h"

#include <iostream>

// definição do membro estático
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

TTF_Font* Resources::GetFont(const std::string& file, int size) {
    // chave única: "arquivo#tamanho"
    std::string key = file + "#" + std::to_string(size);

    auto it = fontTable.find(key);
    if (it != fontTable.end()) {
        return it->second;
    }

    // fonte ainda não carregada — abrir agora
    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if (font == nullptr) {
        std::cerr << "Erro ao carregar fonte: "
                  << file << " (tamanho " << size << ") - "
                  << TTF_GetError() << std::endl;
        return nullptr;
    }

    fontTable[key] = font;
    return font;
}

void Resources::ClearFonts() {
    for (auto& pair : fontTable) {
        TTF_CloseFont(pair.second);
    }
    fontTable.clear();
}
