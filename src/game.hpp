#pragma once

#include "pch.hpp"

class Level;

// Class for managing game context and the main game loop.
class Game {
private:
    std::unique_ptr<Level> _level;

public:
    Game();
    ~Game();

    void run();

};
