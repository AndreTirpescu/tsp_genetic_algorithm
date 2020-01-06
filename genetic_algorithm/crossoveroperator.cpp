#include "crossoveroperator.h"

#include <iostream>
#include <algorithm>

GeneticCrossoverOperator::GeneticCrossoverOperator(Population *pop, GeneticAlgorithmConfig *cfg) 
    : population(pop)
    , configObject(cfg)
{
    crossoverData = new CrossOverObject[pop->getSize()];
}

void GeneticCrossoverOperator::operator()()
{
    fillCrossover();
    sortCrossoverData();

    for (uint32_t i = 0; i < population->getSize() && crossoverData[i].probability < configObject->crossoverProbability; i += 2) {
        crossoverChromosomes(i, i+1);
    }
    
}

void GeneticCrossoverOperator::fillCrossover()
{
    for (uint32_t i = 0; i < population->getSize(); ++i) {
        crossoverData[i].index          = i;
        crossoverData[i].probability    = ((double) rand() / (RAND_MAX));
    }
}

void GeneticCrossoverOperator::sortCrossoverData()
{
    std::sort(
        crossoverData, 
        crossoverData + population->getSize(), 
        [](const CrossOverObject& a, const CrossOverObject& b){
            return a.probability < b.probability;
    });
}

void GeneticCrossoverOperator::crossoverChromosomes(uint32_t c1, uint32_t c2)
{
    population->increaseSize(2);
    
    Chromosome cc1, cc2;
    Chromosome A = population->at(c1);
    Chromosome B = population->at(c2);

    uint32_t sz             = A.getSize();
    uint32_t cutPosition    = rand() %  sz;

    cc1 = A; cc2 = B;

    for (uint32_t i = cutPosition; i < sz; ++i) {
        cc1.set(i, A.at(i));
        cc2.set(i, B.at(i));
    }

    population->addChromosome(cc1);
    population->addChromosome(cc2);
}