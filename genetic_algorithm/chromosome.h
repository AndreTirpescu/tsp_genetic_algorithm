#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "chromosome.h"

#include <cstdint>
#include <vector>
#include <memory>


typedef int Gene;

class Chromosome
{
public:
    Chromosome();
    Chromosome(uint32_t size);

    Chromosome(const Chromosome& obj);

    Chromosome& addGene(Gene gene);
    uint32_t    getSize();
    void        operator=(const Chromosome& obj);
    Gene        at(uint32_t index);
    void        set(uint32_t index, const Gene& chr);
    void        swapGenes(uint32_t geneA, uint32_t geneB);

private:
    uint32_t            size;
    std::vector<Gene>   genes;
};

#endif