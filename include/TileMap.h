#pragma once
#include <memory>

#include <vector>
#include <string>
#include "Component.h"
#include "TileSet.h"

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);

    void Load(const std::string& file);
    void Render() override;
    void RenderLayer(int layer);

private:
    std::vector<int> tileMatrix;
    int mapWidth;
    int mapHeight;
    int mapDepth;

    TileSet* tileSet;
};