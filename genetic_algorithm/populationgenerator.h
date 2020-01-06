#ifndef POPUlATION_GENERATOR_H
#define POPULATION_GENERATOR_H

#include <cstdint>
#include "population.h"

class CustomPopulationGenerator
{
public:
    Population generatePopulation(uint32_t popSz, double delta, uint32_t precision, uint32_t dimension);
};

#endif