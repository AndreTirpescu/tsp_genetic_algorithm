#ifndef POPUlATION_GENERATOR_H
#define POPULATION_GENERATOR_H

#include <cstdint>
#include "population.h"
#include "geneticalgorithmconfig.h"

class CustomPopulationGenerator
{
public:
    Population generatePopulation(const GeneticAlgorithmConfig& config);
};

#endif