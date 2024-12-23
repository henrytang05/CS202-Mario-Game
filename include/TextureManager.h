#pragma once
#include "raylib.h"
#include <map>
#include <string>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    void addTexture(const std::string& key, Texture2D texture) {
        mapTexture[key] = texture;
    }

    Texture2D getTexture(const std::string& key) {
        if(mapTexture.find(key) == mapTexture.end()) {
            throw std::runtime_error("Texture not found");
        }
        return mapTexture[key];
    }

    void addTileset(const std::string& tilesetPath, const std::string& imagePath, int firstGid);

private:
    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::map<std::string, Texture2D> mapTexture;
};