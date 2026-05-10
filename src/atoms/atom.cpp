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
    Color col = BLACK;
    const int TILE_SIZE = 32;

    DrawRectangle(
        _position.x * TILE_SIZE,
        _position.y * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE,
        col
    );
}

Vector2i Atom::get_position() const { return _position; }
void Atom::set_position(Vector2i position) { _position = position; }
