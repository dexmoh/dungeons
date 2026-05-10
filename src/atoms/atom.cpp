#include "atoms/atom.hpp"

#include "game.hpp"

Atom::Atom()
    : _position{ Vector2i(0, 0) }, _offset{ Vector2i(0, 0) }, _ctx{ nullptr }
{}

Atom::~Atom()
{}

void Atom::tick()
{}

void Atom::draw(float delta)
{}

Vector2i Atom::get_position() const { return _position; }
void Atom::set_position(Vector2i position) { _position = position; }
