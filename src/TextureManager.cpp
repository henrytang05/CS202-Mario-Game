#include "pch.h"
#include "TextureManager.h"

using json = nlohmann::json;

void TextureManager::addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstGid) {
    std::ifstream file(tilesetPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << tilesetPath << std::endl;
        return;
    }
    json tilesetData;
    try {
        file >> tilesetData;
    } catch (const json::parse_error& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return;
    }

    Texture2D tilesetImage = LoadTexture(imagePath.c_str());
    Image tilesetImageAsImage = LoadImageFromTexture(tilesetImage);

    int tileWidth = tilesetData["tilewidth"];
    int tileHeight = tilesetData["tileheight"];
    int columns = tilesetData["columns"];

    if (tilesetData.find("tiles") == tilesetData.end()) {
        return;
    }
    for (const auto& tile : tilesetData["tiles"]) {
        if (tile.find("type") == tile.end()) continue;
        std::string type = tile["type"];
        int id = tile["id"];
        float x = (id % columns) * tileWidth;
        float y = (id / columns) * tileHeight;
        Image tileImage = ImageFromImage(tilesetImageAsImage, { x, y, (float)tileWidth, (float)tileHeight });
        Texture2D tileTexture = LoadTextureFromImage(tileImage);
        addTexture(type, tileTexture);
        UnloadImage(tileImage);
    }
    UnloadImage(tilesetImageAsImage);
    UnloadTexture(tilesetImage);
}