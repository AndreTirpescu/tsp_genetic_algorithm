#include "populationgenerator.h"

#include <cmath>
#include <ctime>

Population CustomPopulationGenerator::generatePopulation(uint32_t popSz, double delta, 
    uint32_t precision, uint32_t dimension)
{
    //  N = (b-a)*10d
    uint32_t N          = delta * pow(10, precision);
    uint32_t bitLength  = ceil(log(N));
    uint32_t i, j;
    
    Population result(popSz);

    srand(time(0));

    for (i = 0; i < popSz; ++i) {
        Chromosome c(bitLength * dimension);
        for (j = 0; j < bitLength * dimension; ++j) {
            c.addGene(rand() % 2);
        }
        result.addChromosome(c);
    }
 
    return result;
}