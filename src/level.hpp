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
    Vector2i _size = Vector2i::ZERO;
    Tile* _tiles = nullptr;
    Player* _player = nullptr;

    std::vector<std::unique_ptr<Terrain>> _terrains;
    std::vector<std::unique_ptr<Object>> _objects;
    std::vector<std::unique_ptr<Mob>> _mobs;

    // List of atoms queued to be spawned at the end of the frame.
    std::vector<std::unique_ptr<Atom>> _spawn_queue;

    // List of atoms queued to be deleted at the end of the frame.
    std::vector<Atom*> _deletion_queue;

private:
    void _process_spawn_queue();
    void _process_deletion_queue();

public:
    static constexpr Color DEFAULT_CLEAR_COLOR = (Color) { 5, 18, 18, 255 };
    Color clear_color = DEFAULT_CLEAR_COLOR;

public:
    Level(Vector2i size, std::unique_ptr<Player> player);
    ~Level();

    void ready();                         // Forwards a ready call to all atoms in the level. Called only once.
    void tick();                          // Forwards a tick call to all atoms in the level. Called every tick.
    void update(float delta);             // Forwards an update call to all atoms in the level. Called every frame.
    void draw(CameraBounds bounds) const; // Forwards draw calls to all atoms in the level in correct order. Called every frame.

    bool move_mob(Mob& mob, Vector2i dest);

    // Queue an atom to be spawn at the end of the frame.
    void queue_spawn(std::unique_ptr<Atom> atom);

    // Queue an atom to be deleted at the end of the frame.
    void queue_delete(Atom* atom);

    // Generate a placeholder level for testing.
    static std::unique_ptr<Level> generate_placeholder(Game& ctx);

    Vector2i get_size() const;               // Get level size.
    Tile* get_tile(Vector2i position) const; // Get a tile from the level grid.
    Player* get_player();                    // Get the player atom.

};
