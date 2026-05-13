#include "atoms/terrains/floor.hpp"

#include "texture_manager.hpp"

Floor::Floor() {
    _name = "Floor";
    _description = "This is a floor.";

    set_texture_id(TextureID::FLOORS);
    set_sprite_id(SpriteID::DIRT_FLOOR_TILE_1);
}
