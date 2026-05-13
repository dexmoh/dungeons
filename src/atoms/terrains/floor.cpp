#include "atoms/terrains/floor.hpp"

#include "game.hpp"

Floor::Floor()
    : Terrain()
{}

void Floor::ready(Game* ctx) {
    Terrain::ready(ctx);

    _texture = _ctx->get_tex_manager().get_texture(TextureID::FLOORS);
    set_sprite_id(GetRandomValue(0, 2));

}
