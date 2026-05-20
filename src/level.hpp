#pragma once

#include "pch.hpp"

class Game;
class Tile;
class Player;
class Atom;
class Terrain;
class Object;
class Mob;
struct CameraBounds;

class Level {
private:
    Vector2i _size;
    Tile* _tiles;
    Player& _player;
    std::vector<std::unique_ptr<Atom>> _atoms;

private:
    // Find the index a given atom pointer in the _atoms vector.
    // Returns -1 if the pointer wasn't found.
    int _find_atom(const Atom& atom) const;

public:
    Color clear_color;
    static constexpr Color DEFAULT_CLEAR_COLOR = (Color) { 5, 18, 18, 255 };

public:
    Level(Vector2i size, std::unique_ptr<Player> player);
    ~Level();

    void ready();                         // Forwards a ready call to all atoms in the level. Called only once.
    void tick();                          // Forwards a tick call to all atoms in the level. Called every tick.
    void update(float delta);             // Forwards an update call to all atoms in the level. Called every frame.
    void draw(CameraBounds bounds) const; // Forwards draw calls to all atoms in the level in correct order. Called every frame.

    bool spawn_terrain(std::unique_ptr<Terrain> terrain, Vector2i position, bool force_replace = false);
    bool spawn_object(std::unique_ptr<Object> object, Vector2i position, bool force_replace = false);
    bool spawn_mob(std::unique_ptr<Mob> mob, Vector2i position, bool force_replace = false);

    bool move_mob(Mob& mob, Vector2i dest);

    // Generate a placeholder level for testing.
    static std::unique_ptr<Level> generate_placeholder(Game& ctx);

    Vector2i get_size() const;               // Get level size.
    Tile* get_tile(Vector2i position) const; // Get a tile from the level grid.
    Player& get_player();                    // Get the player atom.

};
