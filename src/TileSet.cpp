#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file)
    : tileSet(file),
      tileWidth(tileWidth),
      tileHeight(tileHeight)
{
    columns = tileSet.GetWidth() / tileWidth;
    rows = tileSet.GetHeight() / tileHeight;
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    // converter índice para a posição na imagem
    int tileX = index % columns;
    int tileY = index / columns;

    // selecionar o frame
    tileSet.SetFrame(tileY * columns + tileX);

    // renderizar
    tileSet.Render(x, y);
}