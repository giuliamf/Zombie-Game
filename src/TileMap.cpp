#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
    : Component(associated),
      mapWidth(0),
      mapHeight(0),
      tileSet(tileSet)
{
    Load(file);
}

void TileMap::Load(const std::string& file) {
    std::ifstream mapFile(file);
    std::string line;

    std::getline(mapFile, line);
    std::stringstream ss(line);

    ss >> mapWidth;
    ss.ignore();
    ss >> mapHeight;
    ss.ignore();

    tileMatrix.resize(mapWidth * mapHeight);    // converte matriz 2D pra vetor 1D

    int index = 0;

    while (std::getline(mapFile, line)) {
        std::stringstream lineStream(line);

        int tile;

        while (lineStream >> tile) {
            tileMatrix[index] = tile;
            index++;
            lineStream.ignore();
        }
    }
}

void TileMap::Render() {
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            int index = tileMatrix[i * mapWidth + j];

            float x = associated.box.pos.x + j * tileSet->GetTileWidth();
            float y = associated.box.pos.y + i * tileSet->GetTileHeight();

            tileSet->RenderTile(index, x, y);
        }
    }
}
``