#pragma once

#include "pch.hpp"

class Game;

// An object that exists inside the game world.
class Atom {
protected:
    Game* _ctx;

    Vector2i _position; // Atom's x and y position in the tile grid.
    Vector2i _offset;   // Offset from atom's position in pixels.
    float _rotation;    // Sprite rotation with the origin in the center.
    Color _tint;        // Color tint applied to the atom texture.
    bool _solid;        // Whether the atom is solid or not.
    bool _visible;      // Whether the atom is visible or not.

    std::string _name;        // Name of the atom.
    std::string _description; // Description of the atom.

    Texture2D _texture;     // Texture resource used by this atom.
    Rectangle _texture_src; // Location of the sprite in the texture.
    Rectangle _sprite_dest; // Destination of where the sprite should be drawn.
    Vector2 _sprite_origin; // Origin point of the sprite.
    int _sprite_id;         // ID of the sprite stored in the texture resource.

public:
    Atom();
    ~Atom();

    // Called when the object is ready to start getting drawn and processed.
    // Ready is only called once.
    virtual void ready(Game* ctx);

    // Called every tick.
    virtual void tick();

    // Draws atom to the screen every frame.
    void draw() const;

    /* Getters & Setters */
    Vector2i get_position() const;
    bool get_visibility() const;

    void set_position(Vector2i position);
    void set_visibility(bool visible);
    void set_sprite_id(int id);

};
