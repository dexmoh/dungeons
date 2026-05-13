#include "atoms/terrains/wall.hpp"

#include "texture_manager.hpp"

Wall::Wall() {
    _name = "Wall";
    _description = "This is a wall.";

    set_solid(true);
    set_texture_id(TextureID::WALLS);
    set_sprite_id(SpriteID::STONE_WALL_TILE);
}
