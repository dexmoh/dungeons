#pragma once

#include "pch.hpp"

class Game;
enum class TextureID;

// A base class for objects that exist inside the game level.
class Atom {
private:
    Vector2i _position; // Atom's x and y position in the tile grid.
    Vector2 _offset;   // Offset from atom's position in pixels.
    float _rotation;    // Sprite rotation with the origin in the center.
    Color _tint;        // Color tint applied to the atom texture.
    bool _solid;        // Whether the atom is solid or not.
    bool _visible;      // Whether the atom is visible or not.

    Texture2D _texture;     // Texture resource used by this atom.
    Rectangle _texture_src; // Location of the sprite in the texture.
    Rectangle _sprite_dest; // Destination of where the sprite should be drawn.
    Vector2 _sprite_origin; // Origin point of the sprite.
    TextureID _texture_id;  // ID of the texture that needs to be loaded.
    int _sprite_id;         // ID of the sprite stored in the texture resource.

protected:
    Game* _ctx; // Game context.

    std::string _name;        // Name of the atom.
    std::string _description; // Description of the atom.

public:
    enum SpriteID {
        DEFAULT_TILE = 0
    };

    Atom();
    ~Atom();

    virtual void ready(Game* ctx);    // Called when the atom is ready to begin being processed.
    virtual void tick();              // Called every tick.
    virtual void update(float delta); // Called every frame.

    // Draws atom to the screen every frame.
    void draw() const;

    /* Getters & Setters */
    Vector2i get_position() const;
    Vector2 get_offset() const;
    float get_rotation() const;
    bool get_solid() const;
    bool get_visibility() const;

    void set_position(Vector2i position);
    void set_offset(Vector2 offset);
    void set_rotation(float rotation);
    void set_solid(bool solid);
    void set_visibility(bool visible);
    void set_texture_id(TextureID id);
    void set_sprite_id(int id);

};
