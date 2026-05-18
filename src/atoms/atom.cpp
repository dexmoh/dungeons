#include "atoms/atom.hpp"

#include "game.hpp"
#include "atom.hpp"

Atom::Atom()
    : _ctx{ nullptr },
      _name{ "Atom" },
      _description{ "You shouldn't be seeing this." },
      _position{ Vector2i::ZERO },
      _offset{ 0.0f, 0.0f },
      _rotation{ 0.0f },
      _tint{ WHITE },
      _solid{ false },
      _visible{ true },
      _sprite_origin{ 0.0f, 0.0f },
      _texture_id{ TextureID::TEST_TILES },
      _sprite_id{ SpriteID::DEFAULT_TILE },
      _flip_h{ false },
      _flip_v{ false }
{}

Atom::~Atom()
{}

void Atom::ready(Game* ctx) {
    _ctx = ctx;

    set_texture_id(_texture_id);
    set_sprite_id(_sprite_id);
    _recalculate_sprite_dest();

    // Initial sprite origin.
    Vector2i tile_size = _ctx->get_tile_size();
    _sprite_origin = {
        tile_size.width() / 2.0f,
        tile_size.height() / 2.0f
    };
}

void Atom::tick() {}
void Atom::update(float delta) {}

void Atom::draw() const {
    if (!_visible)
        return;

    DrawTexturePro(
        _texture,
        _texture_src,
        _sprite_dest,
        _sprite_origin,
        _rotation,
        _tint
    );
}

void Atom::_recalculate_sprite_dest() {
    if (!_ctx)
        return;

    Vector2i tile_size = _ctx->get_tile_size();

    _sprite_dest = {
        float(_position.x * tile_size.width()) + (tile_size.width() / 2.0f) + _offset.x,
        float(_position.y * -tile_size.height() - tile_size.height()) + (tile_size.height() / 2.0f) - _offset.y,
        float(tile_size.height()),
        float(tile_size.width())
    };
}

/* Getters & Setters */
Vector2i Atom::get_position() const { return _position; }
Vector2 Atom::get_offset() const { return _offset; }
float Atom::get_rotation() const { return _rotation; }
bool Atom::get_solid() const { return _solid; }
bool Atom::get_visibility() const { return _visible; }
bool Atom::get_flip_h() const { return _flip_h; }
bool Atom::get_flip_v() const { return _flip_v; }

void Atom::set_position(Vector2i position) {
    _position = position;
    _recalculate_sprite_dest();
}

void Atom::set_offset(Vector2 offset) {
    _offset = offset;
    _recalculate_sprite_dest();
}

void Atom::set_rotation(float rotation) {
    _rotation = rotation;
}

void Atom::set_solid(bool solid) {
    _solid = solid;
}

void Atom::set_visibility(bool visible) {
    _visible = visible;
}

void Atom::set_texture_id(TextureID id) {
    _texture_id = id;

    if (!_ctx)
        return;

    _texture = _ctx->get_tex_manager().get_texture(_texture_id);
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

    if (_flip_h)
        _texture_src.width = -_texture_src.width;

    if (_flip_v)
        _texture_src.height = -_texture_src.height;
}

void Atom::set_flip_h(bool flip_h) {
    if (_flip_h == flip_h)
        return;

    _flip_h = flip_h;
    _texture_src.width = -_texture_src.width;
}

void Atom::set_flip_v(bool flip_v) {
    if (_flip_v == flip_v)
        return;

    _flip_v = flip_v;
    _texture_src.height = -_texture_src.height;;
}
