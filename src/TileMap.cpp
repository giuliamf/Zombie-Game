#include "TileMap.h"
#include "GameObject.h"
#include <fstream>
#include <sstream>

#include <iostream>

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
    : Component(associated),
      mapWidth(0),
      mapHeight(0),
      mapDepth(0),
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
    ss >> mapDepth;
    ss.ignore();

    tileMatrix.clear();
    tileMatrix.reserve(mapWidth * mapHeight * mapDepth);

    while (std::getline(mapFile, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream lineStream(line);
        std::string tileValue;

        while (std::getline(lineStream, tileValue, ',')) {
            if (tileValue.find_first_not_of(" \t\r\n") == std::string::npos) {
                continue;
            }

            tileMatrix.push_back(std::stoi(tileValue));
        }
    }
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDepth; layer++) {
        RenderLayer(layer);
    }
}

void TileMap::RenderLayer(int layer) {
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            int index = layer * (mapWidth * mapHeight) + i * mapWidth + j;

            if (index >= static_cast<int>(tileMatrix.size())) {
                continue;
            }

            int tile = tileMatrix[index];


            float x = associated.box.pos.x + j * tileSet->GetTileWidth();
            float y = associated.box.pos.y + i * tileSet->GetTileHeight();

            tileSet->RenderTile(tile, x, y);
        }
    }
}