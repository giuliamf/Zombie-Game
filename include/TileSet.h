#pragma once

#include <string>
#include "Sprite.h"

class TileSet {
public:
    TileSet(int tileWidth, int tileHeight, const std::string& file);

    TileSet(const TileSet&) = delete;
    TileSet& operator=(const TileSet&) = delete;

    void RenderTile(unsigned index, float x, float y);

    int GetTileWidth();
    int GetTileHeight();

private:
    Sprite tileSet;
    int tileWidth;
    int tileHeight;

    int columns;
    int rows;
};