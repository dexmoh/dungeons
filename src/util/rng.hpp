#pragma once

#include <random>
#include <cstdint>

// Class for generating random numbers.
class RandomNumberGenerator {
private:
    std::mt19937 _engine;
    std::uint32_t _seed;

    std::uniform_int_distribution<int> _int_dist;
    std::uniform_real_distribution<float> _float_dist{ 0.0f, 1.0f };

public:
    RandomNumberGenerator();
    explicit RandomNumberGenerator(std::uint32_t seed);

    // Generates a random integer value in a [0, INT_MAX] range.
    int rand_int();

    // Generates a random integer value in a [min, max] range.
    int rand_int_range(int min, int max);

    // Generates a random floating point value in a [0.0, 1.0] range.
    float rand_float();

    // Generates a random floating point value in a [min, max] range.
    float rand_float_range(float min, float max);

    void randomize_seed();
    void set_seed(std::uint32_t new_seed);
    std::uint32_t get_seed() const;

};
