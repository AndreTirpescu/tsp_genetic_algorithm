#include "population.h"

#include <cstring>
#include "chromosome.h"

#ifdef GENETIC_DEBUG
    #include <iostream>
#endif

#include <cmath>

Population::Population()
{
    populationSize  = 0;
}

Population::Population(uint32_t populationSize) : populationSize(populationSize)
{}

Population& Population::addChromosome(Chromosome chromosome)
{
    if (chromosomes.size() >= populationSize) {
#ifdef GENETIC_DEBUG
        std::cout << "Cannot add chromosome\n";
#endif
        return *this;
    }

    chromosomes.push_back(chromosome);

    return *this;
}

const Chromosome& Population::at(uint32_t index)
{
    if (index > populationSize) {
#ifdef GENETIC_DEBUG
        std::cout << "Index greater than currently set\n";
#endif
    }

    return chromosomes[index];
}

void Population::set(uint32_t index, const Chromosome& chr)
{
    if (index > chromosomes.size()) {
#ifdef GENETIC_DEBUG
        std::cout << "Index greater than currently set\n";
#endif
    }

    chromosomes[index] = chr;
}

uint32_t Population::getSize()
{
    return populationSize;
}

void Population::increaseSize(uint32_t sz)
{
    populationSize += sz;
}

void Population::setSize(uint32_t sz)
{
    populationSize = sz;
}

void Population::reset(const Population& newPop)
{
    chromosomes.clear();
    populationSize = newPop.populationSize;
    
    for (auto it : newPop.chromosomes) {
        chromosomes.push_back(it);
    }
}