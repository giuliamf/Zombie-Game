#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file)
    : tileSet(file),
      tileWidth(tileWidth),
      tileHeight(tileHeight)
{
    columns = tileSet.GetWidth() / tileWidth;
    rows = tileSet.GetHeight() / tileHeight;
    tileSet.SetFrameCount(columns, rows);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    tileSet.SetFrame(static_cast<int>(index));
    tileSet.Render((int)x, (int)y);
}