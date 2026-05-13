#include "atoms/terrains/wall.hpp"

#include "game.hpp"

void Wall::ready(Game *ctx) {
    Terrain::ready(ctx);

    _texture = _ctx->get_tex_manager().get_texture(TextureID::WALLS);
}
