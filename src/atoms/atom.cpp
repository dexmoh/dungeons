#include "atoms/atom.hpp"

#include "game.hpp"
#include "atom.hpp"

Atom::Atom()
    : _position{ Vector2i::ZERO },
      _offset{ Vector2i::ZERO },
      _rotation{ 0.0f },
      _tint{ WHITE },
      _sprite_origin{ 0.0f, 0.0f },
      _sprite_id{ 0 },
      _ctx{ nullptr }
{}

Atom::~Atom()
{}

void Atom::ready(Game* ctx) {
    _ctx = ctx;
    _texture = _ctx->get_tex_manager().get_texture(TextureID::TEST_TILES);

    set_sprite_id(_sprite_id);
    set_position(_position);

    // Initial sprite origin.
    Vector2i tile_size = _ctx->get_tile_size();
    _sprite_origin = {
        tile_size.width() / 2.0f,
        tile_size.height() / 2.0f
    };
}

void Atom::tick()
{}

void Atom::draw() const {
    DrawTexturePro(
        _texture,
        _texture_src,
        _sprite_dest,
        _sprite_origin,
        _rotation,
        _tint
    );
}

Vector2i Atom::get_position() const { return _position; }

void Atom::set_position(Vector2i position) {
    _position = position;

    if (!_ctx)
        return;

    Vector2i tile_size = _ctx->get_tile_size();

    // Recalculate sprite destination based on new position.
    _sprite_dest = {
        float(_position.x * tile_size.width()) + (tile_size.width() / 2.0f),
        float(_position.y * -tile_size.height() - tile_size.height()) + (tile_size.height() / 2.0f),
        float(tile_size.height()),
        float(tile_size.width())
    };
}

void Atom::set_sprite_id(int id) {
    _sprite_id = id;

    if (!_ctx)
        return;

    // Recalculate texture source based on the new sprite ID.
    Vector2i tile_size = _ctx->get_tile_size();
    int tiles_per_row = _texture.width / tile_size.width();

    _texture_src = {
        float((_sprite_id % tiles_per_row) * tile_size.width()),
        float((_sprite_id / tiles_per_row) * tile_size.height()),
        float(tile_size.width()),
        float(tile_size.height())
    };
}
