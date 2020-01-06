#include "mutationoperator.h"
#include <cstdlib>

#include <iostream>


GeneticMutationOperator::GeneticMutationOperator(Population *pop, GeneticAlgorithmConfig *cfg) 
    : population(pop)
    , configObject(cfg)
{}

void GeneticMutationOperator::operator()()
{
    // very ugly
    for (uint32_t chr = 0; chr < population->getSize(); ++chr) {
        Chromosome chromosome = population->at(chr);
        
        for (uint32_t g = 0; g < chromosome.getSize(); ++g) {
            double randomNumber = ((double) rand() / (RAND_MAX)); 
            
            if (configObject->mutationProbability > randomNumber) {
                chromosome.set(g, !chromosome.at(g));
            }
        }

        population->set(chr, chromosome);
    }
}