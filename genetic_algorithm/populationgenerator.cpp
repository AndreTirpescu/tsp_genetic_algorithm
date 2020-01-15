#include "populationgenerator.h"

#include <cmath>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

Population CustomPopulationGenerator::generatePopulation(const GeneticAlgorithmConfig& config)
{
    uint32_t ii, jj;

    Population result(config.populationSize);
    
    std::mt19937 randomNumberGenerator(time(0));
 
    for (ii = 0; ii < config.populationSize; ++ii) {
        Chromosome c(config.dimension);
        
        std::vector<int> nodes;
        for (jj = 1; jj <= config.dimension; ++jj) {
            nodes.push_back(jj);
        }

        std::shuffle(nodes.begin(), nodes.end(), randomNumberGenerator);

        for (auto it : nodes) {
            c.addGene(it);
        }

        result.addChromosome(c);
    }

    return result;
}