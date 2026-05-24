#pragma once

#include "pch.hpp"
#include "texture_manager.hpp"

class Game;
enum class TextureID;

// A base abstract class for objects that exist inside the game level.
class Atom {
public:
    enum class BaseType : std::uint8_t {
        TERRAIN, OBJECT, MOB
    };

    enum SpriteID : std::uint8_t {
        DEFAULT_TILE = 0
    };

private:
    Vector2i _position = Vector2i::ZERO;
    Vector2 _offset = { 0.0f, 0.0f };
    float _rotation = 0.0f;
    Color _tint = WHITE;

    Vector2 _sprite_origin = { 0.0f, 0.0f };
    TextureID _texture_id = TextureID::TEST_TILES;
    int _sprite_id = SpriteID::DEFAULT_TILE;
    std::int16_t _z_index = 0;

    bool _visible = true;
    bool _solid = false;
    bool _flip_h = false;
    bool _flip_v = false;

    Texture2D _texture;
    Rectangle _texture_src;
    Rectangle _sprite_dest;

private:
    void _recalculate_sprite_dest();

protected:
    Game& _ctx;

    std::string _name = "Atom";
    std::string _description = "You shouldn't be seeing this.";

protected:
    Atom(Game& ctx, BaseType base_type);

public:
    const BaseType BASE_TYPE;

    // Emitted right before the atom is about to be deleted.
    Signal<> deleted;

public:
    virtual ~Atom() = default;

    virtual void ready();             // Called when the atom is ready to begin being processed.
    virtual void tick();              // Called every tick.
    virtual void update(float delta); // Called every frame.

    // Draws atom to the screen every frame.
    void draw() const;

    // Queue the atom to be deleted at the end of this frame.
    void queue_delete();

    /* Getters & Setters */
    Vector2i get_position() const;
    Vector2 get_offset() const;
    float get_rotation() const;
    std::int16_t get_z_index() const;
    bool get_visibility() const;
    bool get_solid() const;
    bool get_flip_h() const;
    bool get_flip_v() const;

    void set_position(Vector2i position);
    void set_offset(Vector2 offset);
    void set_rotation(float rotation);
    void set_solid(bool solid);
    void set_visibility(bool visible);
    void set_texture_id(TextureID id);
    void set_sprite_id(int id);
    void set_flip_h(bool flip_h);
    void set_flip_v(bool flip_v);

};
