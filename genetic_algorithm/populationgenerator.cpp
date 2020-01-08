#include "populationgenerator.h"

#include <cmath>
#include <ctime>

Population CustomPopulationGenerator::generatePopulation(const GeneticAlgorithmConfig& config)
{
    uint32_t N          = (config.dimension - 1) * pow(10, config.precision);
    uint32_t bitLength  = ceil(log2(N));
    uint32_t ii, jj;

    Population result(config.populationSize);

    srand(time(0));

    for (ii = 0; ii < config.populationSize; ++ii) {
        Chromosome c(bitLength * config.dimension);
        
        for (jj = 0; jj < bitLength * config.dimension; ++jj) {
            c.addGene(rand() % 2);
        }

        result.addChromosome(c);
    }

    return result;
}