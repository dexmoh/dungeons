#include "util/rng.hpp"

RandomNumberGenerator::RandomNumberGenerator()
    : RandomNumberGenerator(std::random_device{}())
{}

RandomNumberGenerator::RandomNumberGenerator(std::uint32_t seed)
    : _seed{ seed }, _engine{ seed }
{}

int RandomNumberGenerator::rand_int() {
    return _int_dist(_engine);
}

int RandomNumberGenerator::rand_int_range(int min, int max) {
    if (min > max) {
        int tmp = min;
        min = max;
        max = tmp;
    }

    std::uniform_int_distribution<int> dist(min, max);
    return dist(_engine);
}

float RandomNumberGenerator::rand_float() {
    return _float_dist(_engine);
}

float RandomNumberGenerator::rand_float_range(float min, float max) {
    if (min > max) {
        float tmp = min;
        min = max;
        max = tmp;
    }

    std::uniform_real_distribution<float> dist(min, max);
    return dist(_engine);
}

void RandomNumberGenerator::randomize_seed() {
    _seed = std::random_device{}();
    _engine.seed(_seed);
}

void RandomNumberGenerator::set_seed(std::uint32_t new_seed) {
    _seed = new_seed;
    _engine.seed(new_seed);
}

std::uint32_t RandomNumberGenerator::get_seed() const {
    return _seed;
}
