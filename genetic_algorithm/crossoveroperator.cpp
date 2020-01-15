#include "crossoveroperator.h"

#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>

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
    srand(time(0));
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
    srand(time(0));
    
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


void GeneticCrossoverOperator::crossoverChromosomesPMX(uint32_t c1, uint32_t c2)
{
    population->increaseSize(2);

    Chromosome A = population->at(c1);
    Chromosome B = population->at(c2);

    Chromosome C1 = copyToChild(A);
    Chromosome C2 = copyToChild(B);

    uint32_t chromosomeSize = A.getSize();
    uint32_t genePieceSize = getRandomGenePieceSize(chromosomeSize);
    uint32_t startPosition = getStartPosition(genePieceSize, chromosomeSize);

    std::vector<int> mappingC1(A.getSize() + 1, -1);
    std::vector<int> mappingC2(A.getSize() + 1, -1);

    for (uint32_t i = startPosition; i < startPosition + genePieceSize; ++i) {
        C1.set(i, B.at(i));
        C2.set(i, A.at(i));
        mappingC1[ B.at(i) ] = A.at(i);
        mappingC2[ A.at(i) ] = B.at(i);
    }

    for (uint32_t i = 0; i < startPosition; ++i) {
        cleanChildChromosome(C1, mappingC1, i);
        cleanChildChromosome(C2, mappingC2, i);
    }

    for (uint32_t i = startPosition + genePieceSize; i < chromosomeSize; ++i) {
        cleanChildChromosome(C1, mappingC1, i);
        cleanChildChromosome(C2, mappingC2, i);
    }

    population->addChromosome(C1);
    population->addChromosome(C1);
}


Chromosome GeneticCrossoverOperator::copyToChild(Chromosome& parent)
{
    Chromosome result(parent.getSize());

    for (uint32_t i = 0; i < parent.getSize(); ++i) {
        result.addGene(parent.at(i));
    }

    return result;
}

int GeneticCrossoverOperator::getRandomGenePieceSize(uint32_t chromosomeSize)
{
    std::mt19937 randomNumberGenerator(time(0));
    std::uniform_int_distribution<int> distribution(0, chromosomeSize - 2);

    return distribution(randomNumberGenerator);
}

int GeneticCrossoverOperator::getStartPosition(uint32_t genePieceSize, uint32_t chromosomeSize)
{
    std::mt19937 randomNumberGenerator(time(0));
    std::uniform_int_distribution<int> distribution(0, chromosomeSize - genePieceSize);

    return distribution(randomNumberGenerator);
}

int GeneticCrossoverOperator::extractFromMapping(const std::vector<int>& mapping, int index)
{
    int next = mapping[index];
    int current = next;

    while (mapping[next] != -1) {
        current = next;
        next = mapping[next];
    }

    return current;
}

void GeneticCrossoverOperator::cleanChildChromosome(Chromosome& child, const std::vector<int>& mapping, int index)
{
    int mappedGene = extractFromMapping(mapping, index);
        
    if (-1 != mappedGene) {
        child.set(index, mappedGene);
    }
}