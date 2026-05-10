#pragma once

#include "pch.hpp"

class Game;

// An object that exists inside the game world.
class Atom {
protected:
    Game* _ctx;

    Vector2i _position; // Atom's x and y position in the tile grid.
    Vector2i _offset;   // Offset from atom's position in pixels.

public:
    Atom();
    ~Atom();

    // Called when the object is ready to start getting drawn and processed.
    // Ready is only called once.
    virtual void ready(Game* ctx);

    // Called every tick.
    virtual void tick();

    // Used for drawing things to the screen during rendering.
    virtual void draw(float delta);

    Vector2i get_position() const;
    void set_position(Vector2i position);

};
