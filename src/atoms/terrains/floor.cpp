#include "atoms/terrains/floor.hpp"

#include "texture_manager.hpp"

Floor::Floor(Game& ctx)
    : Terrain(ctx)
{
    _name = "Floor";
    _description = "This is a floor. You walk on it.";

    set_texture_id(TextureID::FLOORS);
    set_sprite_id(SpriteID::DIRT_FLOOR_TILE_1);
}
