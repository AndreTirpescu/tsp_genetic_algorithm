#ifndef POPULATION_H
#define POPULATION_H

#include <cstdint>
#include <vector>

#include "chromosome.h"

class Population
{
public:
    Population();

    Population(uint32_t populationSize);

    Population& addChromosome(Chromosome chromosome);

    const Chromosome& at(uint32_t index);
    void             set(uint32_t index, const Chromosome& chr);

    uint32_t    getSize();
    void        increaseSize(uint32_t sz);
    void        setSize(uint32_t sz);
    void        reset(const Population& newPop);

private:
    uint32_t                    populationSize;
    std::vector<Chromosome>     chromosomes;  
};

#endif