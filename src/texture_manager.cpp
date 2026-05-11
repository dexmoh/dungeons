#include "texture_manager.hpp"

TextureManager::TextureManager()
{}

TextureManager::~TextureManager() {
    // Unload stored textures.
    for (const auto& [id, tex] : _textures) {
        UnloadTexture(tex);
    }
}

void TextureManager::init() {
    for (const auto& [id, path] : _S_TEXTURE_PATHS) {
        _textures[id] = LoadTexture(
            (_S_BASE_TEX_DIR + path).c_str()
        );
    }
}

Texture2D TextureManager::get_texture(TextureID id) const { return _textures.at(id); }
