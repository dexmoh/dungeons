#pragma once

#include "pch.hpp"

enum class TextureID {
    TEST_TILES,
    FLOORS,
    WALLS
};

// Class for loading and storing textures.
class TextureManager {
private:
    inline static std::string _BASE_TEX_DIR = "assets/textures/";

    inline static const std::unordered_map<TextureID, const char *> _TEXTURE_PATHS = {
        { TextureID::TEST_TILES, "test_tiles.png" },
        { TextureID::FLOORS, "floors.png" },
        { TextureID::WALLS, "walls.png" }
    };

    std::unordered_map<TextureID, Texture2D> _textures;

public:
    TextureManager();
    ~TextureManager();

    void init();

    Texture2D get_texture(TextureID id) const;

};
