#include "atoms/atom.hpp"

#include "game.hpp"

Atom::Atom()
    : _position{ Vector2i(0, 0) }, _offset{ Vector2i(0, 0) }, _ctx{ nullptr }
{}

Atom::~Atom()
{}

void Atom::ready(Game* ctx) {
    _ctx = ctx;
}

void Atom::tick()
{}

void Atom::draw(float delta) {
    auto tile_size = _ctx->get_tile_size();
    Color col = BLACK;

    if (_position.x == 0 && _position.y == 0)
        col = BLUE;
    else if (_position.x == 0 && _position.y == 1)
        col = GREEN;
    else if (_position.x == 1 && _position.y == 0)
        col = RED;

    DrawRectangle(
        _position.x * tile_size.x,
        _position.y * -tile_size.y - tile_size.y,
        tile_size.x,
        tile_size.y,
        col
    );
}

Vector2i Atom::get_position() const { return _position; }
void Atom::set_position(Vector2i position) { _position = position; }
