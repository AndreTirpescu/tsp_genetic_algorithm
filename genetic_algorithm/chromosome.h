#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "chromosome.h"

#include <cstdint>
#include <vector>
#include <memory>


typedef bool Gene;

class Chromosome
{
public:
    Chromosome();
    Chromosome(uint32_t size);

    Chromosome& addGene(Gene gene);
    uint32_t    getSize();
    void        operator=(const Chromosome& ob);
    Gene        at(uint32_t index);
    void        set(uint32_t index, const Gene& chr);

private:
    uint32_t            size;
    std::vector<Gene>   genes;
};

#endif