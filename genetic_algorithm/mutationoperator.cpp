#include "mutationoperator.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

GeneticMutationOperator::GeneticMutationOperator(Population *pop, GeneticAlgorithmConfig *cfg) 
    : population(pop)
    , configObject(cfg)
{}

void GeneticMutationOperator::operator()()
{
    std::mt19937 randomNumberGenerator(time(0));
    std::uniform_real_distribution<double> distribution(0, 1);
    

    for (uint32_t chr = 0; chr < population->getSize(); ++chr) {
        Chromosome chromosome = population->at(chr);

        double randomNumber = distribution(randomNumberGenerator); 

        if (configObject->mutationProbability > randomNumber) {
            std::uniform_int_distribution<int> distribution(0, chromosome.getSize());

            uint32_t randomGeneA = distribution(randomNumberGenerator);
            uint32_t randomGeneB = distribution(randomNumberGenerator);

            chromosome.swap(randomGeneA, randomGeneB);
        }
    
        population->set(chr, chromosome);
    }
}