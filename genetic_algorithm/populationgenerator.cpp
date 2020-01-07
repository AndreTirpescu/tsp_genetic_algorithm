#include "populationgenerator.h"

#include <cmath>
#include <ctime>

Population CustomPopulationGenerator::generatePopulation(const GeneticAlgorithmConfig& config)
{
    const uint32_t  BIT_LENGTH = 32;
    uint32_t        popIndex;
    uint32_t        chrIndex;
    uint32_t        chrSize;
    uint32_t        number;

    Population result(config.populationSize);

    srand(time(0));

    for (popIndex = 0; popIndex < config.populationSize; ++popIndex) {
        
        chrSize = BIT_LENGTH * config.dimension;

        Chromosome c(chrSize);

        

        for(chrIndex = 0; chrIndex < chrSize; ++chrIndex) {
            number = rand() % 5 + 1;
            
            while (number)
            {
                c.addGene(number % 2);
                number /= 10;
            }
        }

        result.addChromosome(c);
    
    }
 
    return result;
}