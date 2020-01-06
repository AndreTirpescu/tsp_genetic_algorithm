#ifndef GENETIC_ALGORITHM_CONFIG
#define GENETIC_ALGORITHM_CONFIG

#include <cstdint>

struct GeneticAlgorithmConfig
{
    uint32_t    populationSize;
    uint32_t    maxGenerations;
    double      mutationProbability;
    double      crossoverProbability;
    uint32_t    precision;
    uint32_t    dimension;
};


#endif