#ifndef GENETIC_ALGORITHM_CONFIG
#define GENETIC_ALGORITHM_CONFIG

#include <cstdint>

struct GeneticAlgorithmConfig
{
    uint32_t  POPULATION_SIZE;
    uint32_t  MAX_GENERATIONS;
    double    MUTATION_PROBABILITY;
    double    CROSSOVER_PROBABILITY;
    uint32_t  PRECISION;
};


#endif